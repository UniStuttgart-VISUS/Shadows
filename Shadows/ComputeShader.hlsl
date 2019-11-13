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
    float4 texData;
    uint4 texSize;
};

Texture2DMS<float4> Input : register(t0);
RWTexture2D<float4> Output : register(u0);
RWTexture2DArray<int> HEAD : register(u1);
RWTexture2DArray<int> TAIL : register(u2);

[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    // check DTid
    if (any(DTid.xy >= texSize.xy))
    {
        return;
    }

	//Depth Transformation
        float depth = Input.Load(int2(DTid.xy), 0).x;

	// Calcuate Clip Space
	float x = (DTid.x/texData.x) * 2.0f - 1.0f;
	float y = (1 - (DTid.y/texData.y)) * 2.0f - 1.0f;
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
    // TEST IZB

    float u = lightSpacePosition.x * 80;
    float v = lightSpacePosition.y * 45;


    //TAIL[int3(DTid.xy, 0)] = u * 1280;
    //TAIL[int3(DTid.xy, 1)] = v * 720;

    //HEAD[int3(DTid.xy, 0)] = u * 80;
    //HEAD[int3(DTid.xy, 1)] = v * 45;

	/*
	// PSEUDOCODE IZB
	if (HEAD[int3(u, v, 0)] == 0 && HEAD[int3(u, v, 1)] == 0)
	{
		HEAD[int3(u, v, 0)] = DTid.x;
		HEAD[int3(u, v, 1)] = DTid.y;

	}
	else
	{
		int2 index = int2(HEAD[int3(u, v, 0)], HEAD[int3(u, v, 1)]);
		while (TAIL[int3(index, 0)] != 0 || TAIL[int3(index, 1)] != 0)
		{
			index = int2(TAIL[int3(index, 0)], TAIL[int3(index, 1)]);
		}
		TAIL[int3(index, 0)] = DTid.x;
		TAIL[int3(index, 1)] = DTid.y;

	}
	*/
	
}