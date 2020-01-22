#include "Header.hlsli"
#include "SharedConstants.h"

RWBuffer<int> HEAD : register(u0);
RWBuffer<int> ListLengthBuffer : register(u1);

struct TailSample {
    float3 ws_pos;
    int next;
};
RWStructuredBuffer<TailSample> TailBuffer : register(u2);

struct TailNewSample {
    float4 ws_pos;
};
RWStructuredBuffer<TailNewSample> TailBufferNew : register(u3);

struct HeadNewSample {
    int4 offsetListLen;
};
RWStructuredBuffer<HeadNewSample> HeadBufferNew : register(u4);


cbuffer CSConstants : register(b1) {
    float4x4 viewInv;
    float4x4 projInv;
    float4x4 viewProj;
    float4x4 meshWorld;
    float4x4 characterWorld;
    float4 texData;
    uint4 texSize;
    uint4 headSize;
    uint4 vertexCount;
    float3 lightDir;
};


[numthreads(64, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID) {
    // Skip unnecessary threads...
    if (DTid.x >= headSize.x * headSize.y) {
        return;
    }

    //calculate offset
    int offset = 0;
    for (uint i = 0; i < DTid.x; ++i) {
        offset = offset + ListLengthBuffer[i];
    }
    
    HeadBufferNew[DTid.x].offsetListLen = int4(offset, ListLengthBuffer[DTid.x], 0, 0);
    /*
    //fill new tailbuffer
    int next = HEAD[DTid.x];
    for (int j = 0; j < ListLengthBuffer[DTid.x]; ++j) {
        TailBufferNew[offset + j].ws_pos = float4(TailBuffer[next].ws_pos, 0.0);
        next = TailBuffer[next].next;
    }

    //fill new headbuffer
    HeadBufferNew[DTid.x].offsetListLen = int4(offset, ListLengthBuffer[DTid.x], 0, 0);
    */
}