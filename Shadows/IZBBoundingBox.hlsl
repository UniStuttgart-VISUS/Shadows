#include "Header.hlsli"
#include "SharedConstants.h"

StructuredBuffer<uint> Indices : register(t0);
Buffer<float3> Vertices : register(t1);
RWBuffer<uint> Output : register(u0);


cbuffer CSConstants : register(b1) {
	float4x4 viewInv;
	float4x4 projInv;
	float4x4 viewProj;
	float4x4 meshWorld;
	float4x4 characterWorld;
	float4 texData;
	uint4 texSize;
	uint4 headSize;
	uint4 vertexCount;
    float3 lightDir;
};


[numthreads(64, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID) {
	// Skip unnecessary threads...
	if (DTid.x >= vertexCount.x) {
		return;
	}

	// Get the triangles.
	int3 triangleIndices = int3(Indices.Load(DTid.x * 3 + 0),
		Indices.Load(DTid.x * 3 + 1), Indices.Load(DTid.x * 3 + 2));
	float3 v0 = Vertices.Load(triangleIndices.x);
	float3 v1 = Vertices.Load(triangleIndices.y);
	float3 v2 = Vertices.Load(triangleIndices.z);

	// Transformation to world space
	float4 v0_ws = mul(float4(v0, 1.0f), meshWorld).xyzw;
	float4 v1_ws = mul(float4(v1, 1.0f), meshWorld).xyzw;
	float4 v2_ws = mul(float4(v2, 1.0f), meshWorld).xyzw;

	// Transformation to Light Space via orthographic projection
	float4 v0_ls = mul(viewProj, v0_ws);
	float4 v1_ls = mul(viewProj, v1_ws);
	float4 v2_ls = mul(viewProj, v2_ws);

	// Vertex scaling.
	int v0_u = v0_ls.x * headSize.x;
	int v0_v = v0_ls.y * headSize.y;

	int v1_u = v1_ls.x * headSize.x;
	int v1_v = v1_ls.y * headSize.y;

	int v2_u = v2_ls.x * headSize.x;
	int v2_v = v2_ls.y * headSize.y;

	// BOUNDING BOX 
	// (minX, minY)     (maxX, minY)
	//        _________
	//       |   /\   |
	//       |  /  \  |
	//       | /    \ |
	//       |/______\|
	// (minX, maxY)     (maxX, maxY)

	// CALCULATE BOUNDING BOX 
	int minX = floor(min(v0_u, min(v1_u, v2_u)));
	int minY = floor(min(v0_v, min(v1_v, v2_v)));
	int maxX = ceil(max(v0_u, max(v1_u, v2_u)));
	int maxY = ceil(max(v0_v, max(v1_v, v2_v)));

    minX = max(0, minX);
    minY = max(0, minY);
    maxX = min(headSize.x, maxX);
    maxY = min(headSize.y, maxY);

	// Compute the index.
	uint index = 0;
	int bbSize = (1 + maxX - minX) * (1 + maxY - minY);
	if (bbSize > 16 && bbSize <= 64) {
		index = 1;
	} else if (bbSize > 64 && bbSize <= 128) {
		index = 2;
	} else if (bbSize > 128 && bbSize <= 256) {
		index = 3;
	} else if (bbSize > 256) {
		index = 4;
	}

	// Save the output to the buffer.
	int idx = DTid.x * 6;
	Output[idx + 0] = uint(minX);
	Output[idx + 1] = uint(minY);
	Output[idx + 2] = uint(maxX);
	Output[idx + 3] = uint(maxY);
	Output[idx + 4] = index;
	Output[idx + 5] = DTid.x;
}


