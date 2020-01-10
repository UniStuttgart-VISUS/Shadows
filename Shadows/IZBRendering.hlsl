#include "Header.hlsli"
#include "SharedConstants.h"

StructuredBuffer<uint> Indices : register(t0);
Buffer<float3> Vertices : register(t1);
Texture2D<float4> WORLDPOS : register(t2);
Texture2D<int> HEAD : register(t3);
Texture2D<int> TAIL : register(t4);
Buffer<uint> BBoxData : register(t5);
RWTexture2D<int> VISMASK : register(u0);


//ray-triangle based on the Möller–Trumbore  intersection algorithm
bool RayIntersectsTriangle(float3 rayOrigin, float3 rayVector, float3 vertex0,
		float3 vertex1, float3 vertex2) {
    const float EPSILON = 0.0000001f;
    bool result = false;
    
    float3 edge1 = vertex1 - vertex0;
    float3 edge2 = vertex2 - vertex0;
    
    float3 h = cross(rayVector, edge2);
    float a = dot(edge1, h); 
    if (a > -EPSILON && a < EPSILON) {
        result = false; // This ray is parallel to this triangle.
    } else {
        float f = 1.0 / a;
        float3 s = rayOrigin - vertex0;
        float u = f * dot(s, h);
        if (u < 0.0 || u > 1.0) {
            result = false;
        } else {
            float3 q = cross(s, edge1);
            float v = f * dot(rayVector, q);
            if (v < 0.0 || u + v > 1.0) {
                result = false;
            } else {
                // At this stage we can compute t to find out where the intersection
				// point is on the line.
                float t = f * dot(edge2, q);
                if (t > EPSILON && t < 1 / EPSILON) {
                    result = true;
                } else {
                    // This means that there is a line intersection but not a ray
					// intersection.
                    result = false;
                }
            }
        }
    }
    return result;
}


// Hilfsfunktion Dreieckszahl
uint f(uint w) {
	return (w * (w + 1)) / 2;
}

// Hilfsfunktion untere Dreieckswurzel
uint q(uint z) {
	return floor((sqrt(8 * z + 1) - 1) / 2);
}

// returns a single, unique value given two integer values x and y
int pairingFunction(int2 tuple) {
	return tuple.y + 0.5 * (tuple.x + tuple.y) * (tuple.x + tuple.y + 1);
}

// calculates the inverse pairing function of an intger z to get x and y
int2 inversePairingFunction(int z) {
	int pi2 = z - f(q(z));
	int pi1 = q(z) - pi2;
	return int2(pi1, pi2);
}


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


[numthreads(64, 8, 1)]
void main(uint3 DTid : SV_DispatchThreadID) {
	// Skip unnecessary threads...
	uint id = DTid.x + vertexCount.y;
	if (id >= vertexCount.z) {
		return;
	}

	// Get the triangles.
	uint tIdx = BBoxData[id * 6 + 5];
	int3 triangleIndices = int3(Indices.Load(tIdx * 3 + 0),
		Indices.Load(tIdx * 3 + 1), Indices.Load(tIdx * 3 + 2));
	float3 v0 = Vertices.Load(triangleIndices.x);
	float3 v1 = Vertices.Load(triangleIndices.y);
	float3 v2 = Vertices.Load(triangleIndices.z);

	// Transformation to world space
	float4 v0_ws = mul(float4(v0, 1.0f), meshWorld).xyzw;
	float4 v1_ws = mul(float4(v1, 1.0f), meshWorld).xyzw;
	float4 v2_ws = mul(float4(v2, 1.0f), meshWorld).xyzw;

	// Get bounding box corner values.
	uint minX = BBoxData[id * 6 + 0];
	uint minY = BBoxData[id * 6 + 1];
	uint maxX = BBoxData[id * 6 + 2];
	uint maxY = BBoxData[id * 6 + 3];
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
		int2 samplePoint = inversePairingFunction(value);
	
		// Load the world coordinates for the sample point.
		float3 samplePoint_ws = WORLDPOS[samplePoint].xyz;
	
		// Adjust samplepoint to avoid self intersection.
		float3 adjustedSamplePoint_ws = samplePoint_ws + 0.025f * lightDir;
	
		// Check if sample point intersects with the current triangle.
		bool intersection = RayIntersectsTriangle(adjustedSamplePoint_ws,
			lightDir, v0_ws.xyz, v1_ws.xyz, v2_ws.xyz);
		if (intersection) {
			// The sample point is shadowed.
			VISMASK[samplePoint] = 0;
		}
	
		// Get next sample point from the TAIL texture.
		value = TAIL[samplePoint];
	}
}