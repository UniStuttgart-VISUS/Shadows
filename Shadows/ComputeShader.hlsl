#include "Header.hlsli"
#include "SharedConstants.h"

//=================================================================================================
// Constants
//=================================================================================================


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

Texture2DMS<float4> Input : register(t0);
RWTexture2D<float4> Output : register(u0);
RWTexture2D<int> HEAD : register(u1);
RWTexture2D<int> TAIL : register(u2);

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

[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    // check DTid
	if (any(DTid.xy >= texSize.xy))
	{
		return;
	}

	// Depth Transformation
	float depth = Input.Load(int2(DTid.xy), 0).x;
    
    // Discard Skybox
	if (depth > 0.9999f)
	{
		return;
	}

	// Calcuate Clip Space
	float x = (DTid.x / texData.x) * 2.0f - 1.0f;
	float y = (1 - (DTid.y / texData.y)) * 2.0f - 1.0f;
	float4 clipSpacePosition = float4(x, y, depth, 1.0f);

	// Transformation to ViewSpace
	float4 viewSpacePosition = mul(projInv, clipSpacePosition);

	// Perspective division
	viewSpacePosition /= viewSpacePosition.w;

	// Transformation to world space
	float4 worldSpacePosition = mul(viewInv, viewSpacePosition);

	// Transformation to Light Space via orthographic projection
	float4 lightSpacePosition = mul(viewProj, worldSpacePosition);

    Output[int2(DTid.xy)] = float4(lightSpacePosition.xyz, 1.0f);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // IZB

	int u = lightSpacePosition.x * headSize.x;
	int v = lightSpacePosition.y * headSize.y;
    
	// map x and y to a single, unique integer z
    int z = pairingFunction(DTid.xy);
	
    // NEW IZB with paired values
	int lastID = -2;
    
	//write index to head 
	InterlockedExchange(HEAD[int2(u, v)], z, lastID);
	
	//save last index in tail 
	TAIL[int2(DTid.xy)] = lastID;
    

  
}
    
    