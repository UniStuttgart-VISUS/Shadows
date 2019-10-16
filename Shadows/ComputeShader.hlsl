#include "Header.hlsli"
#include "SharedConstants.h"

//=================================================================================================
// Constants
//=================================================================================================


cbuffer CSConstants : register(b1)
{
    float4x4 viewInv;
    float4x4 projInv;
};

Texture2DMS<float4> Input : register(t0);
RWTexture2D<float4> Output : register(u0);


[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
	float4 bla = float4(1, 1, 1, 1);
	float4 test = mul(viewInv, bla); //cbuffer works
	float4 depth = Input.Load(int2(DTid.xy),0).x;
    Output[int2(DTid.xy)] = depth;

}