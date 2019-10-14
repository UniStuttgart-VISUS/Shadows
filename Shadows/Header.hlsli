/// <copyright file="hlsltypemapping.hlsli" company="SFB-TRR 161 Quantitative Methods for Visual Computing">
/// Copyright © 2016 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>
/// <author>Florian Frieß</author>

/// <copyright file="typemapping.hlsli" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2014 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>
/// <author>Florian Frieß</author>

#ifdef _MSC_VER
#pragma once

typedef DirectX::XMFLOAT2 float2;
typedef DirectX::XMFLOAT3 float3;
typedef DirectX::XMFLOAT4 float4;

typedef DirectX::XMINT2 int2;
typedef DirectX::XMINT3 int3;
typedef DirectX::XMINT4 int4;

typedef DirectX::XMFLOAT4X4 float4x4;

typedef uint32_t uint;
typedef DirectX::XMUINT2 uint2;
typedef DirectX::XMUINT3 uint3;
typedef DirectX::XMUINT4 uint4;

#define cbuffer __declspec(align(16)) struct

#define CBUFFER(slot)

#else /* _MSC_VER */

#define CBUFFER(slot) : register(b##slot)

#endif /* _MSC_VER */