#include "Header.hlsli"
#include "SharedConstants.h"

StructuredBuffer<uint> Indices : register(t0);
Buffer<float3> Vertices : register(t1);
Buffer<int> HEAD : register(t2);

struct BBoxSample {
	uint4 bbox;
	uint4 indices;
};
RWStructuredBuffer<BBoxSample> OutputBBox : register(u0);
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
	float4 v0_ws = mul(meshWorld, float4(v0, 1.0f)).xyzw;
	float4 v1_ws = mul(meshWorld, float4(v1, 1.0f)).xyzw;
	float4 v2_ws = mul(meshWorld, float4(v2, 1.0f)).xyzw;

	// Transformation to Light Space via orthographic projection
	float4 v0_ls = mul(viewProj, v0_ws);
	float4 v1_ls = mul(viewProj, v1_ws);
	float4 v2_ls = mul(viewProj, v2_ws);

	bool reject = (v0_ls.x < 0.0 && v1_ls.x < 0.0 && v2_ls.x < 0.0) ||
		(v0_ls.x > 1.0 && v1_ls.x > 1.0 && v2_ls.x > 1.0) ||
		(v0_ls.y < 0.0 && v1_ls.y < 0.0 && v2_ls.y < 0.0) ||
		(v0_ls.y > 1.0 && v1_ls.y > 1.0 && v2_ls.y > 1.0);
	if (reject) {
		return;
	}

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
    maxX = min(headSize.x -1, maxX);
    maxY = min(headSize.y -1, maxY);

	// Compute the index.
	uint index = 0;
	int bbSize = (1 + maxX - minX) * (1 + maxY - minY);
	if (bbSize > 2 && bbSize <= 4) {
		index = 1;
	} else if (bbSize > 4 && bbSize <= 8) {
		index = 2;
	} else if (bbSize > 8 && bbSize <= 64) {
		index = 3;
	} else if (bbSize > 64 && bbSize <= 512) {
		index = 4;
	} else if (bbSize > 512 && bbSize <= 8192) {
		index = 5;
	} else if (bbSize > 8192) {
		index = 6;
	}

	// Check if the head texture has at least one value that is not -1.
	if (index < 6) {
		// Only do this for smaller bounding boxes.
		int2 counts = int2(0, 0);
		for (int j = minY; j <= maxY; ++j) {
			for (int i = minX; i <= maxX; ++i) {
				if (HEAD[j * headSize.x + i] == -1) {
					counts.x++;
				}
				counts.y++;
			}
		}
	
		// The bounding box would not change anything in the output so dropp it.
		if (counts.x == counts.y) {
			return;
		}
	}

	// Increase the counter for the histogram bin and used the returned value as the
	// index for the output buffer.
	uint oldVal = 0;
	InterlockedAdd(OutputHist[index], 1, oldVal);

	// Save the output to the buffer.
	int idx = (index * vertexCount.x) + oldVal;
	OutputBBox[idx].bbox = uint4(minX, minY, maxX, maxY);
	OutputBBox[idx].indices = uint4(DTid.x, 0, 0, 0);
}