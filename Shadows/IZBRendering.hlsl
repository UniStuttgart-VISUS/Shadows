#include "Header.hlsli"
#include "SharedConstants.h"

StructuredBuffer<uint> Indices : register(t0);
Buffer<float3> Vertices : register(t1);
RWTexture2D<float4> Output : register(u0);
RWTexture2D<int> HEAD : register(u1);
RWTexture2D<int> TAIL : register(u2);
RWTexture2D<int> VISMASK : register(u3);


//ray-triangle based on the Möller–Trumbore  intersection algorithm
bool RayIntersectsTriangle(float3 rayOrigin,
                           float3 rayVector,
                           float3 vertex0, float3 vertex1, float3 vertex2)
{
    const float EPSILON = 0.0000001f;

    bool result = false;
    
    float3 edge1 = vertex1 - vertex0;
    float3 edge2 = vertex2 - vertex0;
    
    float3 h = cross(rayVector, edge2);
    
    float a = dot(edge1, h); 
   
    if (a > -EPSILON && a < EPSILON)
    {
        result = false; // This ray is parallel to this triangle.
    }
    else
    {
        
        float f = 1.0 / a;
        float3 s = rayOrigin - vertex0;
        float u = f * dot(s, h);
        if (u < 0.0 || u > 1.0)
        {
            result = false;
        }
        else
        {
            float3 q = cross(s, edge1);
            float v = f * dot(rayVector, q);
            if (v < 0.0 || u + v > 1.0)
            {
                result = false;
            }
            else
            {
                
                // At this stage we can compute t to find out where the intersection point is on the line.
                float t = f * dot(edge2, q);
                if (t > EPSILON && t < 1 / EPSILON) // ray intersection
                {
                //intersectionPoint = rayOrigin + rayVector * t;
                    result = true;
                }
                else
                {
                    // This means that there is a line intersection but not a ray intersection.
                    result = false;
        
                }
                
            }
            
            
        }
    }

    return result;
}


// Hilfsfunktion Dreieckszahl
uint f(uint w)
{
	return (w * (w + 1)) / 2;
}

// Hilfsfunktion untere Dreieckswurzel
uint q(uint z)
{
	return floor((sqrt(8 * z + 1) - 1) / 2);
}

// returns a single, unique value given two integer values x and y
int pairingFunction(int2 tuple)
{
	return tuple.y + 0.5 * (tuple.x + tuple.y) * (tuple.x + tuple.y + 1);
}

// calculates the inverse pairing function of an intger z to get x and y
int2 inversePairingFunction(int z)
{
	int pi2 = z - f(q(z));
	int pi1 = q(z) - pi2;
	return int2(pi1, pi2);
}


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


[numthreads(256, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
	if (DTid.x >= vertexCount.x) {
		return;
	}
    

	int3 triangleIndices = int3(Indices.Load(DTid.x * 3 + 0), Indices.Load(DTid.x * 3 + 1), Indices.Load(DTid.x * 3 + 2));

	float3 v0 = Vertices.Load(triangleIndices.x);
	float3 v1 = Vertices.Load(triangleIndices.y);
	float3 v2 = Vertices.Load(triangleIndices.z);
	/*
	
	float3 v0;
	v0.x = Vertices.Load(triangleIndices.x * 3 + 0);
	v0.y = Vertices.Load(triangleIndices.x * 3 + 1);
	v0.z = Vertices.Load(triangleIndices.x * 3 + 2);
	float3 v1;
	v1.x = Vertices.Load(triangleIndices.y * 3 + 0);
	v1.y = Vertices.Load(triangleIndices.y * 3 + 1);
	v1.z = Vertices.Load(triangleIndices.y * 3 + 2);
	float3 v2;
	v2.x = Vertices.Load(triangleIndices.z * 3 + 0);
	v2.y = Vertices.Load(triangleIndices.z * 3 + 1);
	v2.z = Vertices.Load(triangleIndices.z * 3 + 2);
	*/

	// Transformation to world space
	float4 v0_ws = mul(float4(v0, 1.0f), meshWorld).xyzw;
	float4 v1_ws = mul(float4(v1, 1.0f), meshWorld).xyzw;
	float4 v2_ws = mul(float4(v2, 1.0f), meshWorld).xyzw;

	// Transformation to Light Space via orthographic projection
	float4 v0_ls = mul(viewProj, v0_ws);
	float4 v1_ls = mul(viewProj, v1_ws);
	float4 v2_ls = mul(viewProj, v2_ws);

	int v0_u = v0_ls.x * headSize.x;
	int v0_v = v0_ls.y * headSize.y;

	int v1_u = v1_ls.x * headSize.x;
	int v1_v = v1_ls.y * headSize.y;

	int v2_u = v2_ls.x * headSize.x;
	int v2_v = v2_ls.y * headSize.y;

    
	// CALCULATE BOUNDING BOX 
	int minX = floor(min(v0_u, min(v1_u, v2_u)));
	int minY = floor(min(v0_v, min(v1_v, v2_v)));
	int maxX = ceil(max(v0_u, max(v1_u, v2_u)));
	int maxY = ceil(max(v0_v, max(v1_v, v2_v)));

    
	
    
    // BOUNDING BOX 
	// (minX, minY)     (maxX, minY)
	//        _________
	//       |   /\   |
	//       |  /  \  |
	//       | /    \ |
	//       |/______\|
	// (minX, maxY)     (maxX, maxY)

    [unroll(10)]
    for (int i = minX; i <= maxY; ++i)
	{
        [unroll(10)]
        for (int j = minY; j <= maxY; ++j)
        {
            
            int value = HEAD[int2(i, j)];
          
            //iterate over all the sample points in the izb lists 
            while (value != -1)
            {
                int2 samplePoint = inversePairingFunction(value);
                 
                //load the world coordinates for the sample point
                float3 samplePoint_ws = Output[samplePoint].xyz;
                
                //check if sample point intersects with the current triangle 
                if (RayIntersectsTriangle(samplePoint_ws+1.0f*-lightDir, -lightDir, v0_ws.xyz, v1_ws.xyz, v2_ws.xyz ))
                {
                    
                    //save that the point is in the shadow
                    VISMASK[samplePoint] = 0;
                }

                //get next sample point from tail texture
                value = TAIL[samplePoint];
            }
    
        }

	}
    
}


