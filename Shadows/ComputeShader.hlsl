#include "Header.hlsli"
#include "SharedConstants.h"

//=================================================================================================
// Constants
//=================================================================================================


cbuffer CSConstants : register(b1)
{
    float4x4 viewInv;
    float4x4 projInv;
    float width;
    float height;
	float4x4 viewProj;
};

Texture2DMS<float4> Input : register(t0);
RWTexture2D<float4> Output : register(u0);

float4x4 OrthographicProjection(float l, float b, float r,
	float t, float zn, float zf)
{
	return float4x4(float4(2.0f / (r - l), 0, 0, 0),
		float4(0, 2.0f / (t - b), 0, 0),
		float4(0, 0, 1 / (zf - zn), 0),
		float4((l + r) / (l - r), (t + b) / (b - t), zn / (zn - zf), 1));
}

float4x4 LookAtMatrix(float3 eye, float3 at, float3 up) {
		float3 zaxis = normalize(at - eye);
		float3 xaxis = normalize(cross(up, zaxis));
		float3 yaxis = cross(zaxis, xaxis);

		return float4x4(float4(xaxis.x, yaxis.x, zaxis.x, 0),
			float4(xaxis.y, yaxis.y, zaxis.y, 0),
			float4(xaxis.z, yaxis.z, zaxis.z, 0),
			float4(-dot(xaxis, eye), -dot(yaxis, eye), -dot(zaxis, eye), 1));
}

[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{

	//Depth Transformation
	float depth = Input.Load(int2(DTid.xy), 0).x;


	// Calcuate Clip Space
	float x = (DTid.x/width) * 2.0f - 1.0f;
	float y = (1 - (DTid.y/height)) * 2.0f - 1.0f;
	float4 clipSpacePosition = float4(x, y, depth, 1.0f);

	// Transformation to ViewSpace
	float4 viewSpacePosition = mul(projInv, clipSpacePosition);

	// Perspective division
	viewSpacePosition /= viewSpacePosition.w;

	// Transformation to world space
	float4 worldSpacePosition = mul(viewInv, viewSpacePosition);

	// Transformation to Light Space via orthographic projection
	worldSpacePosition = mul(viewProj, worldSpacePosition);

	Output[int2(DTid.xy)] = float4(worldSpacePosition.xyz / 10.0f, 1.0f);
	
}