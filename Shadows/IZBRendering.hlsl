#include "Header.hlsli"
#include "SharedConstants.h"

RWBuffer<float3> VERTEXBUFFER : register(u1);
RWBuffer<float3> INDEXBUFFER : register(u2);

[numthreads(256, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{

}