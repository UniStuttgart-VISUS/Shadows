#include "Header.hlsli"
#include "SharedConstants.h"

RWBuffer<uint> OutputBBox : register(u0);
RWBuffer<uint> OutputHist : register(u1);

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
	if (DTid.x >= vertexCount.x) {
		return;
	}

	// Reset the Bounding Box values for the triangle.
	uint idx = DTid.x * 5;
	OutputBBox[idx + 0] = 0;
	OutputBBox[idx + 1] = 0;
	OutputBBox[idx + 2] = 0;
	OutputBBox[idx + 3] = 0;
	OutputBBox[idx + 4] = 0;

	// Reset the histogram bin count.
	OutputHist[0] = 0;
	OutputHist[1] = 0;
	OutputHist[2] = 0;
	OutputHist[3] = 0;
	OutputHist[4] = 0;
	OutputHist[5] = 0;
	OutputHist[6] = 0;
}