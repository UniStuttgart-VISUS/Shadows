#include "Header.hlsli"
#include "SharedConstants.h"

StructuredBuffer<uint> Indices : register(t0);
Buffer<float3> Vertices : register(t1);
Texture2D<int> HEAD : register(t2);
RWBuffer<uint> OutputBBox : register(u0);
RWBuffer<uint> OutputHist : register(u1);


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

	// Face culling.
	// TODO: does not work 100%...
	float3 camPos = float3(viewInv[0][3], viewInv[1][3], viewInv[2][3]);
	float3 edge1 = v1_ws.xyz - v0_ws.xyz;
	float3 edge2 = v2_ws.xyz - v0_ws.xyz;
	float3 normal = normalize(cross(edge1, edge2));
	float3 viewDir = normalize(v0_ws.xyz - camPos);
	float result = dot(normal, viewDir);
	if (result <= 0.0) {
		//return;
	}

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

	// Make sure the size is positive or at least zero.
    minX = max(0, minX);
    minY = max(0, minY);
    maxX = min(headSize.x, maxX);
    maxY = min(headSize.y, maxY);

	// Check if the head texture has at least one value that is not -1.
	int2 counts = int2(0, 0);
	for (int i = minX; i <= maxX; ++i) {
		for (int j = minY; j <= maxY; ++j) {
			if (HEAD[int2(i, j)] == -1) {
				counts.x++;
			}
			counts.y++;
		}
	}
	if (counts.x == counts.y) {
		return;
	}

	// Compute the index.
	uint index = 0;
	int bbSize = (1 + maxX - minX) * (1 + maxY - minY);
	if (bbSize > 4 && bbSize <= 8) {
		index = 1;
	} else if (bbSize > 8 && bbSize <= 32) {
		index = 2;
	} else if (bbSize > 32 && bbSize <= 128) {
		index = 3;
	} else if (bbSize > 128 && bbSize <= 512) {
		index = 4;
	} else if (bbSize > 512) {
		index = 5;
	}

	// Increase the counter for the histogram bin and used the returned value as the
	// index for the output buffer.
	uint oldVal = 0;
	InterlockedAdd(OutputHist[index], 1, oldVal);

	// Save the output to the buffer.
	int idx = (index * (vertexCount.x * 6)) + (oldVal * 6);
	OutputBBox[idx + 0] = uint(minX);
	OutputBBox[idx + 1] = uint(minY);
	OutputBBox[idx + 2] = uint(maxX);
	OutputBBox[idx + 3] = uint(maxY);
	OutputBBox[idx + 4] = index;
	OutputBBox[idx + 5] = DTid.x;
}