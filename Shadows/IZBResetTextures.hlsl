#include "Header.hlsli"
#include "SharedConstants.h"

RWTexture2D<int> VISMASK : register(u0);
RWTexture2D<int> HEAD : register(u1);
RWTexture2D<int> TAIL : register(u2);
RWBuffer<uint> OutputHist : register(u3);

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

[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID) {
	// Reset the head texture.
	if (all(DTid.xy < headSize.xy)) {
		HEAD[int2(DTid.xy)] = -1;
	}

	// Reset the vismask and tail texture.
	if (all(DTid.xy < headSize.zw)) {
		VISMASK[int2(DTid.xy)] = 1;
		TAIL[int2(DTid.xy)] = -1;
	}

	// Reset the histogram bin count.
	if (DTid.x == 0) {
		OutputHist[0] = 0;
		OutputHist[1] = 0;
		OutputHist[2] = 0;
		OutputHist[3] = 0;
		OutputHist[4] = 0;
		OutputHist[5] = 0;
		OutputHist[6] = 0;
	}
}