//=================================================================================================
//
//	Shadows Sample
//  by MJP
//  http://mynameismjp.wordpress.com/
//
//  All code licensed under the MIT license
//
//=================================================================================================

#pragma once

#include "SampleFramework11/PCH.h"
#include "SampleFramework11/GraphicsTypes.h"
#include "SampleFramework11/PostProcessorBase.h"
#include "SampleFramework11/DeviceStates.h"

#include "AppSettings.h"
#include "SampleFramework11/Camera.h"

using namespace SampleFramework11;

class PostProcessor : public PostProcessorBase
{

public:

    struct Constants
    {
		Float4x4 viewInv;
		Float4x4 projectionInv;
        float BloomThreshold;
        float BloomMagnitude;
        float BloomBlurSigma;
        float Tau;
        float TimeDelta;
        float KeyValue;
		Float4x4 ViewProjInv;
    };

    void Initialize(ID3D11Device* device);

    void SetConstants(const Constants& constants);
    void Render(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* input,
                ID3D11RenderTargetView* output);
    void AfterReset(uint32 width, uint32 height);

    void DrawDepthBuffer(DepthStencilBuffer& depthBuffer, ID3D11RenderTargetView* rt);

	void VisualizePosition(DepthStencilBuffer& depthBuffer, ID3D11RenderTargetView* rt);

	void PostProcessor::VisualizeTexture(ID3D11Texture2D& texture, ID3D11RenderTargetView* rt);

	void PostProcessor::VisualizeTextureInt(ID3D11Texture2D& texture, ID3D11RenderTargetView* rt);

    const Constants& GetConstants() const { return constantBuffer.Data; }

protected:

    void CalcAvgLuminance(ID3D11ShaderResourceView* input);
    void Bloom(ID3D11ShaderResourceView* input, TempRenderTarget*& bloomTarget);
    void ToneMap(ID3D11ShaderResourceView* input, ID3D11ShaderResourceView* bloom,
                 ID3D11RenderTargetView* output);

    PixelShaderPtr bloomThreshold;
    PixelShaderPtr bloomBlurH;
    PixelShaderPtr bloomBlurV;
    PixelShaderPtr luminanceMap;
    PixelShaderPtr composite;
    PixelShaderPtr scale;
    PixelShaderPtr adaptLuminance;
    PixelShaderPtr drawDepth;
    PixelShaderPtr drawDepthMSAA;
	PixelShaderPtr visualizeReconstructedPosition;
	PixelShaderPtr visualizeTexture;
	PixelShaderPtr visualizeTextureInt;

    RenderTarget2D adaptedLuminance[2];
    RenderTarget2D exposureMap;

    uint64 currLumTarget;

    ConstantBuffer<Constants> constantBuffer;
};