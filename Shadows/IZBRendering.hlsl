#include "Header.hlsli"
#include "SharedConstants.h"

StructuredBuffer<uint> Indices : register(t0);
Buffer<float3> Vertices : register(t1);
Texture2D<int> HEAD : register(t2);
Buffer<uint> BBoxData : register(t3);
Buffer<uint> InputHist : register(t4);

struct TailSample {
	float3 ws_pos;
    int next;
};
StructuredBuffer<TailSample> TailBuffer : register(t5);

struct IntersectSample {
	float4 edge1A;
	float4 edge2F;
	float4 h;
};
StructuredBuffer<IntersectSample> IntersectValues : register(t6);


RWTexture2D<int> VISMASK : register(u0);


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


static const float EPSILON = 0.0000001;
static const float INFINITY = 1.0 / EPSILON;


// ray-triangle based on the Möller–Trumbore  intersection algorithm
bool RayIntersectsTriangle(const float3 rayOrigin, const float3 rayVector,
		const float3 vertex0, const float3 edge1, const float3 edge2, const float a,
		const float3 h, const float f) {
	// Compute the values.
	float3 s = rayOrigin - vertex0;
	float u = f * dot(s, h);
	float3 q = cross(s, edge1);
	float v = f * dot(rayVector, q);
	float t = f * dot(edge2, q);

	// Determine the result.
	bool result = false;
	if (u < 0.0 || u > 1.0) {
		result = false;
	} else {
		if (v < 0.0 || u + v > 1.0) {
			result = false;
		} else {
			// At this stage we can compute t to find out where the intersection
			// point is on the line.
			if (t > ::EPSILON && t < ::INFINITY) {
				result = true;
			} else {
				// This means that there is a line intersection but not a ray
				// intersection.
				result = false;
			}
		}
	}
	return result;
}

[numthreads(64, 4, 1)]
void main(uint3 DTid : SV_DispatchThreadID) {
	// Skip unnecessary threads...
	uint id = DTid.x;
	if (id >= InputHist[vertexCount.y]) {
		return;
	}

	// Get the triangles.
	id = vertexCount.y * (vertexCount.x * 5) + (id * 5);
	uint tIdx = BBoxData[id + 4];
	float3 v0 = Vertices.Load(Indices.Load(tIdx * 3));

	// Transformation to world space
	float4 v0_ws = mul(float4(v0, 1.0f), meshWorld).xyzw;

	// Get the precomputed values for the Ray -> Triangle intersection.
	IntersectSample values = IntersectValues[tIdx];
	float3 edge1 = values.edge1A.xyz;
	float a = values.edge1A.w;
	float3 edge2 = values.edge2F.xyz;
	float f = values.edge2F.w;
	float3 h = values.h.xyz;

	// Since this is true for all sample points we can skip the while loop.
	if (a > -EPSILON && a < EPSILON) {
		return;
	}

	// Get bounding box corner values.
	uint minX = BBoxData[id + 0];
	uint minY = BBoxData[id + 1];
	uint maxX = BBoxData[id + 2];
	uint maxY = BBoxData[id + 3];
	uint diffX = (maxX - minX) + 1;

	// Get the coordinates in the bounding box.
	uint xCoord = minX + (DTid.y % diffX);
	uint yCoord = minY + (DTid.y / diffX);

	// Skip unnecessary threads...
	if (any(uint2(xCoord, yCoord) > uint2(maxX, maxY))) {
		return;
	}

	// Get the initial value from the HEAD texture.
	int value = HEAD[int2(xCoord, yCoord)];

	// Iterate over all the sample points in the izb list.
	while (value != -1) {
		// Get the sample point.
		int2 samplePoint = int2(value % texSize.x, floor(value / texSize.x) );
	
		// Get next sample point from the TAIL texture.
        TailSample s = TailBuffer[value];
        float3 samplePoint_ws = s.ws_pos;
        value = s.next;
	
		// Adjust samplepoint to avoid self intersection.
		float3 adjustedSamplePoint_ws = samplePoint_ws + 0.025f * lightDir;
	
		// Check if sample point intersects with the current triangle.
		bool intersection = RayIntersectsTriangle(adjustedSamplePoint_ws,
			lightDir, v0_ws.xyz, edge1, edge2, a, h, f);
		if (intersection) {
			// The sample point is shadowed.
			VISMASK[samplePoint] = 0;
		}
	}
}