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
	float4x4 meshWorld;
	float4x4 characterWorld;
    float4 texData;
    uint4 texSize;
    uint4 headSize;
	uint4 vertexCount;
    float3 lightDir;

};

Texture2DMS<float4> Input : register(t0);
RWBuffer<int> HEAD : register(u0);

struct TailSample {
	float3 ws_pos;
    int next;
};
RWStructuredBuffer<TailSample> TailBuffer : register(u1);
RWBuffer<int> ListLengthBuffer : register(u2);

[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID) {
    // check DTid
	if (any(DTid.xy >= texSize.xy)) {
		return;
	}

	// Depth Transformation
	float depth = Input.Load(int2(DTid.xy), 0).x;
    
    // Discard Skybox
	if (depth > 0.9999f) {
		return;
	}

	// Calcuate Clip Space
	float x = (DTid.x / texData.x) * 2.0f - 1.0f;
	float y = (1 - (DTid.y / texData.y)) * 2.0f - 1.0f;
	float4 clipSpacePosition = float4(x, y, depth, 1.0f);

	// Transformation to ViewSpace
	float4 viewSpacePosition = mul(projInv, clipSpacePosition);

	// Perspective division
	viewSpacePosition /= viewSpacePosition.w;

	// Transformation to world space
	float4 worldSpacePosition = mul(viewInv, viewSpacePosition);

	// Transformation to Light Space via orthographic projection
	float4 lightSpacePosition = mul(viewProj, worldSpacePosition);

    // IZB
    float u_f = lightSpacePosition.x * headSize.x;
    float v_f = lightSpacePosition.y * headSize.y;
    
    int u = floor(u_f);
    int v = floor(v_f);
    
	// map x and y to a single, unique integer z
    int linear_idx = DTid.x + DTid.y * texSize.x;
	
    // NEW IZB with paired values
	int lastID = -2;
    
	//write index to head 
    InterlockedExchange(HEAD[u + v * headSize.x], linear_idx, lastID);
    InterlockedAdd(ListLengthBuffer[u + v * headSize.x], 1);
    
    // compute linear tail pixel index
	TailBuffer[linear_idx].ws_pos = worldSpacePosition.xyz;
    TailBuffer[linear_idx].next = lastID;
}
    
    