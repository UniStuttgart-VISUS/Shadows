#include "Header.hlsli"
#include "SharedConstants.h"

//=================================================================================================
// Constants
//=================================================================================================


cbuffer CSConstants : register(b1)
{
    float4x4 viewInv;
    float4x4 projInv;
    float width;
    float height;
	float4x4 viewProj;
};

Texture2DMS<float4> Input : register(t0);
RWTexture2D<float4> Output : register(u0);
RWTexture2D<int2> HEAD : register(u1);
RWTexture2D<int2> TAIL : register(u2);

[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{

	//Depth Transformation
	float depth = Input.Load(int2(DTid.xy), 0).x;


	// Calcuate Clip Space
	float x = (DTid.x/width) * 2.0f - 1.0f;
	float y = (1 - (DTid.y/height)) * 2.0f - 1.0f;
	float4 clipSpacePosition = float4(x, y, depth, 1.0f);

	// Transformation to ViewSpace
	float4 viewSpacePosition = mul(projInv, clipSpacePosition);

	// Perspective division
	//viewSpacePosition /= viewSpacePosition.w;

	// Transformation to world space
	float4 worldSpacePosition = mul(viewInv, viewSpacePosition);

	// Transformation to Light Space via orthographic projection
    float4 lightSpacePosition = mul(viewProj, worldSpacePosition);

    lightSpacePosition /= lightSpacePosition.w;
    
    Output[int2(DTid.xy)] = float4(lightSpacePosition.xyz, 1.0f);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // TEST IZB

    float u = lightSpacePosition.x / lightSpacePosition.z;
    float v = lightSpacePosition.y / lightSpacePosition.z;


    HEAD[int2(DTid.xy)] = int2(0, 1);
    TAIL[int2(DTid.xy)] = int2(1, 0);

    /*
    // PSEUDOCODE IZB
    if (HEAD_Texture[u, v] == (-1, -1))
    {
        HEAD_Texture[u, v] = DTid.xy;

    }
    else
    {
        int2 index = HEAD_Texture[lightSpacePosition.uv];
        while (TAIL_Texture[index] != (-1, -1))
        {
            index = TAIL_Texture[index];
        }
        TAIL_Texture[index] = DTid.xy;

    }
    */
	
}