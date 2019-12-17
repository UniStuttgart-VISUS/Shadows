#include "Header.hlsli"
#include "SharedConstants.h"
StructuredBuffer<uint> Indices : register(t0);
Buffer<float3> Vertices : register(t1);
RWTexture2D<int> HEAD : register(u0);
RWTexture2D<int> TAIL : register(u1);

cbuffer CSConstants : register(b1)
{
	float4x4 viewInv;
	float4x4 projInv;
	float4x4 viewProj;
	float4x4 meshWorld;
	float4x4 characterWorld;
	float4 texData;
	uint4 texSize;
	uint4 headSize;
};


[numthreads(256, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
	int3 triangleIndices = int3(Indices.Load(DTid.x) * 3, Indices.Load(DTid.x) * 3 + 1, Indices.Load(DTid.x) * 3 + 2);
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
	float4 v2_ls = mul(viewProj, v1_ws);

	// CALCULATE BOUNDING BOX 
	int minX = floor(min(v0_ls.x, min(v1_ls.x, v2_ls.x)));
	int minY = floor(min(v0_ls.y, min(v1_ls.y, v2_ls.y)));
	int maxX = ceil(max(v0_ls.x, max(v1_ls.x, v2_ls.x)));
	int maxY = ceil(max(v0_ls.y, max(v1_ls.y, v2_ls.y)));

	// BOUNDING BOX 
	// (minX, minY)     (maxX, minY)
	//        _________
	//       |   /\   |
	//       |  /  \  |
	//       | /    \ |
	//       |/______\|
	// (minX, maxY)     (maxX, maxY)


	for (int i = minX; i <= maxX; ++i)
	{
		for (int j = minY; j <= maxY; ++j)
		{
			bool inShadow = true;
			// TEST ALL SAMPLES IF THEY ARE IN THE FRUSTUM OF THE TRIANGLE
			if (inShadow)
			{
				// dunkel

			}
			else
			{
				// hell
			}
		}

	}

}