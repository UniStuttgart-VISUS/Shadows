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
    float4 texSize;
};

Texture2DMS<float4> Input : register(t0);
RWTexture2D<float4> Output : register(u0);
RWTexture2DArray<int> HEAD : register(u1);
RWTexture2DArray<int> TAIL : register(u2);

[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{

	//Depth Transformation
    float depth = Input.Load(int2(DTid.xy), 0).x;



	// Calcuate Clip Space
	float x = (DTid.x/texSize.x) * 2.0f - 1.0f;
	float y = (1 - (DTid.y/texSize.y)) * 2.0f - 1.0f;
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

    int u = lightSpacePosition.x;
    int v = lightSpacePosition.y;


    TAIL[int3(DTid.xy, 0)] = u;
    TAIL[int3(DTid.xy, 1)] = v;

    HEAD[int3(DTid.xy, 0)] = u;
    HEAD[int3(DTid.xy, 1)] = v;


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