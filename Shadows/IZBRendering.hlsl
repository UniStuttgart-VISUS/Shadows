#include "Header.hlsli"
#include "SharedConstants.h"
StructuredBuffer<uint> Indices : register(t0);
StructuredBuffer<float3> Vertices : register(t1);
RWTexture2D<int> HEAD : register(u0);
RWTexture2D<int> TAIL : register(u1);

[numthreads(256, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{

}