#include "Header.hlsli"
#include "SharedConstants.h"

StructuredBuffer<uint> Indices : register(t0);
Buffer<float3> Vertices : register(t1);

struct IntersectSample {
	float4 edge1A;
	float4 edge2F;
	float4 h;
};
RWStructuredBuffer<IntersectSample> IntersectValues : register(u0);


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

	// Get the triangles.
	int3 triangleIndices = int3(Indices.Load(DTid.x * 3 + 0),
		Indices.Load(DTid.x * 3 + 1), Indices.Load(DTid.x * 3 + 2));
	float3 v0 = Vertices.Load(triangleIndices.x);
	float3 v1 = Vertices.Load(triangleIndices.y);
	float3 v2 = Vertices.Load(triangleIndices.z);
	
	// Transformation to world space
	float4 v0_ws = mul(float4(v0, 1.0f), meshWorld).xyzw;
	float4 v1_ws = mul(float4(v1, 1.0f), meshWorld).xyzw;
	float4 v2_ws = mul(float4(v2, 1.0f), meshWorld).xyzw;
	
	// Precomputation of values for the Ray -> Triangle intersection.
	float3 edge1 = v1_ws.xyz - v0_ws.xyz;
	float3 edge2 = v2_ws.xyz - v0_ws.xyz;
	float3 h = cross(lightDir, edge2);
	float a = dot(edge1, h);
	float f = 1.0 / a;
	
	// Store the computed values.
	IntersectValues[DTid.x].edge1A = float4(edge1, a);
	IntersectValues[DTid.x].edge2F = float4(edge2, f);
	IntersectValues[DTid.x].h = float4(h, 0.0);
}