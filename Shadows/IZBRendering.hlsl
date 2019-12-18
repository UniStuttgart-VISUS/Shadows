#include "Header.hlsli"
#include "SharedConstants.h"
StructuredBuffer<uint> Indices : register(t0);
Buffer<float3> Vertices : register(t1);
RWTexture2D<int> HEAD : register(u0);
RWTexture2D<int> TAIL : register(u1);


// Hilfsfunktion Dreieckszahl
uint f(uint w)
{
	return (w * (w + 1)) / 2;
}

// Hilfsfunktion untere Dreieckswurzel
uint q(uint z)
{
	return floor((sqrt(8 * z + 1) - 1) / 2);
}

// returns a single, unique value given two integer values x and y
int pairingFunction(int2 tuple)
{
	return tuple.y + 0.5 * (tuple.x + tuple.y) * (tuple.x + tuple.y + 1);
}

// calculates the inverse pairing function of an intger z to get x and y
int2 inversePairingFunction(int z)
{
	int pi2 = z - f(q(z));
	int pi1 = q(z) - pi2;
	return int2(pi1, pi2);
}


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
	uint4 vertexCount;
};


[numthreads(256, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
	if (DTid.x >= vertexCount.x) {
		return;
	}

	int3 triangleIndices = int3(Indices.Load(DTid.x * 3 + 0), Indices.Load(DTid.x * 3 + 1), Indices.Load(DTid.x * 3 + 2));

	float3 v0 = Vertices.Load(triangleIndices.x);
	float3 v1 = Vertices.Load(triangleIndices.y);
	float3 v2 = Vertices.Load(triangleIndices.z);
	/*
	
	float3 v0;
	v0.x = Vertices.Load(triangleIndices.x * 3 + 0);
	v0.y = Vertices.Load(triangleIndices.x * 3 + 1);
	v0.z = Vertices.Load(triangleIndices.x * 3 + 2);
	float3 v1;
	v1.x = Vertices.Load(triangleIndices.y * 3 + 0);
	v1.y = Vertices.Load(triangleIndices.y * 3 + 1);
	v1.z = Vertices.Load(triangleIndices.y * 3 + 2);
	float3 v2;
	v2.x = Vertices.Load(triangleIndices.z * 3 + 0);
	v2.y = Vertices.Load(triangleIndices.z * 3 + 1);
	v2.z = Vertices.Load(triangleIndices.z * 3 + 2);
	*/

	// Transformation to world space
	float4 v0_ws = mul(float4(v0, 1.0f), meshWorld).xyzw;
	float4 v1_ws = mul(float4(v1, 1.0f), meshWorld).xyzw;
	float4 v2_ws = mul(float4(v2, 1.0f), meshWorld).xyzw;

	// Transformation to Light Space via orthographic projection
	float4 v0_ls = mul(viewProj, v0_ws);
	float4 v1_ls = mul(viewProj, v1_ws);
	float4 v2_ls = mul(viewProj, v2_ws);

	int v0_u = v0_ls.x * headSize.x;
	int v0_v = v0_ls.y * headSize.y;

	int v1_u = v1_ls.x * headSize.x;
	int v1_v = v1_ls.y * headSize.y;

	int v2_u = v2_ls.x * headSize.x;
	int v2_v = v2_ls.y * headSize.y;


	// CALCULATE BOUNDING BOX 
	int minX = floor(min(v0_u, min(v1_u, v2_u)));
	int minY = floor(min(v0_v, min(v1_v, v2_v)));
	int maxX = ceil(max(v0_u, max(v1_u, v2_u)));
	int maxY = ceil(max(v0_v, max(v1_v, v2_v)));

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
			int value = HEAD[int2(i, j)];
				while (value != -1) 
				{
					int2 samplePoint = inversePairingFunction(value);
					//raytracing mit samplepoint
					//setzen von Ergebnis in visibility mask
					value = TAIL[samplePoint];

				}
		}

	}

}