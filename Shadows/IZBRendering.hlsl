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

	// TRANSFORMATION TO LIGHT SPACE ( uv - COORDINATES)

	//transform to world space
	float4 v0_ws = mul(float4(v0, 1.0f), meshWorld).xyzw;
	float4 v1_ws = mul(float4(v1, 1.0f), meshWorld).xyzw;
	float4 v2_ws = mul(float4(v2, 1.0f), meshWorld).xyzw;



	// CALCULATE BOUNDING BOX 
	int minX = floor(min(v0.x, min(v1.x, v2.x)));
	int minY = floor(min(v0.y, min(v1.y, v2.y)));
	int maxX = ceil(max(v0.x, max(v1.x, v2.x)));
	int maxY = ceil(max(v0.y, max(v1.y, v2.y)));

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