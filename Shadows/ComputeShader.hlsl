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
    // IZB

    int u = lightSpacePosition.x * 80.0f;
    int v = lightSpacePosition.y * 45.0f;

	
	// PSEUDOCODE IZB
    int headX = -2;
    InterlockedCompareExchange(HEAD[int3(u, v, 0)], -1, DTid.x, headX);
    if (headX == -1)
    {
        InterlockedCompareStore(HEAD[int3(u, v, 1)], -1, DTid.y);
    }
    
    else
    {
        // Spin Lock to make sure headY is written
        int headY = HEAD[int3(u, v, 1)]; //HEAD.Load(int4(u, v, 1, 0)).x;
        [allow_uav_condition]
        while (headY == -1)
        {
            headY = HEAD[int3(u, v, 1)]; //HEAD.Load(int4(u, v, 1, 0)).x;
        }

        // headX and headY are written

        int tailX = -2;
        InterlockedCompareExchange(TAIL[int3(headX, headY, 0)], -1, DTid.x, tailX);
        if (tailX == -1)
        {
            InterlockedCompareStore(TAIL[int3(u, v, 1)], -1, DTid.y);

        }
        else
        {
            // while loop to search for free index
            [allow_uav_condition]
            while (tailX != -1)
            {
                // spin lock to make sure that tailY ia written
                int tailY = TAIL[int3(u, v, 1)]; //HEAD.Load(int4(u, v, 1, 0)).x;
                [allow_uav_condition]
                while (tailY == -1)
                {
                    tailY = TAIL[int3(u, v, 1)]; //TAIL.Load(int4(u, v, 1, 0)).x;

                }

                // tailX and tailY are written
                InterlockedCompareExchange(TAIL[int3(tailX, tailY, 0)], -1, DTid.x, tailX);
                if (tailX == -1)
                {
                    InterlockedCompareStore(TAIL[int3(u, v, 1)], -1, DTid.y);

                }
            
            }
        }


    }
    /*

	if (HEAD[int3(u, v, 0)] == -1 && HEAD[int3(u, v, 1)] == -1)
	{
		//HEAD[int3(u, v, 0)] = DTid.x;
		//HEAD[int3(u, v, 1)] = DTid.y;
        InterlockedCompareStore(HEAD[int3(u, v, 0)], -1, DTid.x);
        InterlockedCompareStore(HEAD[int3(u, v, 1)], -1, DTid.y);

	}
	else
    {
        int2 index = int2(HEAD[int3(u, v, 0)], HEAD[int3(u, v, 1)]);
        while (TAIL[int3(index, 0)] != -1 || TAIL[int3(index, 1)] != -1)
        {
            index = int2(TAIL[int3(index, 0)], TAIL[int3(index, 1)]);
        }
        //TAIL[int3(index, 0)] = DTid.x;
        //TAIL[int3(index, 1)] = DTid.y;
        InterlockedCompareStore(TAIL[int3(index, 0)], -1, DTid.x);
        InterlockedCompareStore(TAIL[int3(index, 1)], -1, DTid.y);
        

    }*/	
}