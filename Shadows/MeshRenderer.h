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

#include <array>

#include "SampleFramework11/PCH.h"

#include "SampleFramework11/Model.h"
#include "SampleFramework11/GraphicsTypes.h"
#include "SampleFramework11/DeviceStates.h"
#include "SampleFramework11/Camera.h"
#include "SampleFramework11/SH.h"
#include "SampleFramework11/ShaderCompilation.h"
#include "ComputeShader.h"
#include "IZBBoundingBox.h"
#include "IZBIntersectionPre.h"
#include "IZBLinearization.h"
#include "IZBRendering.h"
#include "IZBRenderingBig.h"
#include "IZBResetTextures.h"
#include "AppSettings.h"
#include "SharedConstants.h"

using namespace SampleFramework11;

// Represents a bouncing sphere for a MeshPart
struct Sphere
{
	XMFLOAT3 Center;
	float Radius;
};

// Represents the 6 planes of a frustum
Float4Align struct Frustum
{
	XMVECTOR Planes[6];
};

struct MeshData
{
	Model* Model;
	ID3D11BufferPtr PositionsVB;
	StructuredBuffer Indices;
	StructuredBuffer DrawCalls;
	StructuredBuffer CulledDraws;
	RWBuffer CulledIndices;

	std::vector<Sphere> BoundingSpheres;
	std::vector<uint32> FrustumTests;
	uint32 NumSuccessfulTests;

	std::vector<ID3D11InputLayoutPtr> InputLayouts;
	std::vector<ID3D11InputLayoutPtr> DepthInputLayouts;

	MeshData() : Model(NULL), NumSuccessfulTests(0) {}
};

class MeshRenderer
{

protected:

	// Constants
	static const uint32 MaxReadbackLatency = 4;
	static const uint32 MaxBlurRadius = 4;

public:

	MeshRenderer();

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* context, DepthStencilBuffer& depthBuffer);
	void InitializeIZB(ID3D11Device* device, ID3D11DeviceContext* context, DepthStencilBuffer& depthBuffer, uint32 backbuffer_width, uint32 backbuffer_height);
	void SetSceneMesh(ID3D11DeviceContext* context, Model* model, const Float4x4& world);
	void SetCharacterMesh(ID3D11DeviceContext* context, Model* model, const Float4x4& world);

	void RenderDepthCPU(ID3D11DeviceContext* context, const Camera& camera, const Float4x4& world,
		const Float4x4& characterWorld, bool shadowRendering);
	void RenderDepthGPU(ID3D11DeviceContext* context, const Camera& camera, const Float4x4& world,
		const Float4x4& characterWorld, bool shadowRendering);

	void Render(ID3D11DeviceContext* context, const Camera& camera, const Float4x4& world,
		const Float4x4& characterWorld);

	void RenderShadowMap(ID3D11DeviceContext* context, const Camera& camera,
		const Float4x4& world, const Float4x4& characterWorld);
	void RenderShadowMapGPU(ID3D11DeviceContext* context, const Camera& camera,
		const Float4x4& world, const Float4x4& characterWorld);

	ID3D11Texture2D* RenderIZB(ID3D11DeviceContext* context, DepthStencilBuffer& depthBuffer, const Camera& camera, const Float4x4& meshWorld, const Float4x4& characterWorld);

	void Update();

	void CreateReductionTargets(uint32 width, uint32 height);

	void ReduceDepth(ID3D11DeviceContext* context, ID3D11ShaderResourceView* depthTarget,
		const Camera& camera);

	DepthStencilBuffer& ShadowMap() { return shadowMap; }

protected:

	void LoadShaders();
	void CreateShadowMaps();
	void ConvertToVSM(ID3D11DeviceContext* context, uint32 cascadeIdx,
		Float3 cascadeScale, Float3 cascade0Scale);

	void SetupRenderDepthState(ID3D11DeviceContext* context, bool shadowRendering);

	void RenderDepthGPU(ID3D11DeviceContext* context, const Float4x4& world,
		const Float4x4& characterWorld, bool shadowRendering,
		ID3D11Buffer* viewProj, uint32 viewProjOffset,
		ID3D11Buffer* frustumPlanes, uint32 planesOffset);

	void RenderModelDepthGPU(ID3D11DeviceContext* context, MeshData& meshData, bool shadowRendering,
		const Float4x4& world, ID3D11Buffer* viewProj, uint32 viewProjOffset,
		ID3D11Buffer* frustumPlanes, uint32 planeOffset);
	void RenderModelDepthCPU(ID3D11DeviceContext* context, const Camera& camera, const Float4x4& world,
		MeshData& meshData);

	void RenderModel(ID3D11DeviceContext* context, const Camera& camera, const Float4x4& world,
		MeshData& meshData);

	ID3D11DevicePtr device;

	BlendStates blendStates;
	RasterizerStates rasterizerStates;
	DepthStencilStates depthStencilStates;
	SamplerStates samplerStates;

	MeshData scene;
	MeshData character;

	ID3D11ShaderResourceViewPtr defaultTexture;

	DepthStencilBuffer shadowMap;
	RenderTarget2D  varianceShadowMap;
	RenderTarget2D tempVSM;

	ID3D11ShaderResourceViewPtr randomRotations;

	ID3D11RasterizerStatePtr shadowRSState;
	ID3D11SamplerStatePtr evsmSamplers[uint64(ShadowAnisotropy::NumValues)];

	VertexShaderPtr meshVS;
	PixelShaderPtr meshPS;

	VertexShaderPtr meshDepthVS;

	VertexShaderPtr fullScreenVS;
	PixelShaderPtr vsmConvertPS[AppSettings::NumFilterableShadowModes][uint64(ShadowMSAA::NumValues)];
	PixelShaderPtr vsmBlurH[MaxBlurRadius + 1];
	PixelShaderPtr vsmBlurV[MaxBlurRadius + 1];
	PixelShaderPtr vsmBlurGPUH;
	PixelShaderPtr vsmBlurGPUV;

	PixelShaderPtr depthReductionInitialPS;
	PixelShaderPtr depthReductionPS;
	ComputeShaderPtr depthReductionInitialCS;
	ComputeShaderPtr depthReductionCS;
	std::vector<RenderTarget2D> depthReductionTargets;
	StagingTexture2D reductionStagingTextures[MaxReadbackLatency];
	uint32 currFrame;

	Float2 reductionDepth;

	ComputeShaderPtr clearArgsBuffer;
	ComputeShaderPtr cullDrawCalls;
	ComputeShaderPtr batchDrawCalls;
	RWBuffer drawArgsBuffer;
	ID3D11InputLayoutPtr depthGPUInputLayout;
	RWBuffer batchDispatchArgs;

	ComputeShaderPtr setupCascades;
	StructuredBuffer cascadeMatrixBuffer;
	StructuredBuffer cascadeSplitBuffer;
	StructuredBuffer cascadeOffsetBuffer;
	StructuredBuffer cascadeScaleBuffer;
	StructuredBuffer cascadePlanesBuffer;

	// Constant buffers
	struct DepthOnlyConstants
	{
		Float4x4 World;
		Float4x4 ViewProjection;
	};

	struct MeshVSConstants
	{
		Float4x4 World;
		Float4x4 ViewProjection;
	};

	struct MeshPSConstants
	{
		Float4Align Float3 CameraPosWS;

		Float4Align Float4x4 ShadowMatrix;
		Float4Align float CascadeSplits[NumCascades];

		Float4Align Float4 CascadeOffsets[NumCascades];
		Float4Align Float4 CascadeScales[NumCascades];
        Float4Align uint useIZB;
	};

	struct VSMConstants
	{
		Float4 CascadeScale;
		Float4 Cascade0Scale;
		Float2 ShadowMapSize;
	};

	struct ReductionConstants
	{
		Float4x4 Projection;
		float NearClip;
		float FarClip;
	};

	struct GPUBatchConstants
	{
		Float4 FrustumPlanes[6];
		uint32 NumDrawCalls;
		bool32 CullNearZ;
	};

	struct ShadowSetupConstants
	{
		Float4x4 GlobalShadowMatrix;
		Float4x4 ViewProjInv;
		Float3 CameraRight;
		float CameraNearClip;
		float CameraFarClip;
	};

	struct FrustumConstants
	{
		Float4 FrustumPlanes[6];
	};

	struct ComputeShaderConstants
	{
		Float4x4 viewInv;
		Float4x4 projInv;
		Float4x4 viewProj;
		Float4x4 meshWorld;
		Float4x4 characterWorld;
		float4 texData;
		uint4 texSize;
		uint4 headSize;
		uint4 vertexCount;
		float3 lightDir;
	};

	ConstantBuffer<DepthOnlyConstants> depthOnlyConstants;
	ConstantBuffer<MeshVSConstants> meshVSConstants;
	ConstantBuffer<MeshPSConstants> meshPSConstants;
	ConstantBuffer<VSMConstants> vsmConstants;
	ConstantBuffer<ReductionConstants> reductionConstants;
	ConstantBuffer<GPUBatchConstants> gpuBatchConstants;
	ConstantBuffer<ShadowSetupConstants> shadowSetupConstants;

	ConstantBuffer<Float4x4> tempViewProjBuffer;
	ConstantBuffer<FrustumConstants> tempFrustumPlanesBuffer;

	ConstantBuffer<ComputeShaderConstants> computeShaderConstants;

	ID3D11UnorderedAccessView* verticesUAV;
	ID3D11UnorderedAccessView* visMapUAV;

	ID3D11ShaderResourceView* vertexBufferSRV;
	ID3D11ShaderResourceView* worldPosSRV;
	ID3D11ShaderResourceView* visMapSRV;


	ID3D11Texture2D* visMap;
	ID3D11Buffer* vertexBuffer;

	ID3D11Query* queryObj;
	D3D11_QUERY_DESC queryDesc;
	std::vector<ID3D11ShaderResourceView*> srvsInterPre;
	std::vector<ID3D11ShaderResourceView*> srvsHistComp;
	std::vector<ID3D11ShaderResourceView*> srvsRendering;
	std::vector<ID3D11ShaderResourceView*> srvsReset;
	std::vector<ID3D11UnorderedAccessView*> uavsClear;
	std::vector<ID3D11UnorderedAccessView*> uavsCreation;
	std::vector<ID3D11UnorderedAccessView*> uavsLin;
	std::vector<ID3D11UnorderedAccessView*> uavsHistComp;
	std::vector<ID3D11UnorderedAccessView*> uavsInterPre;
	std::vector<ID3D11UnorderedAccessView*> uavsRendering;
	std::vector<ID3D11UnorderedAccessView*> uavsReset;

	ID3D11ComputeShader* boundingBoxCS;
	ID3D11ComputeShader* intersectionCS;
	ID3D11ComputeShader* izbCreationCS;
	ID3D11ComputeShader* izbLinearizationCS;
	ID3D11ComputeShader* izbRenderingCS;
	ID3D11ComputeShader* izbRenderingBigCS;
	ID3D11ComputeShader* izbResetCS;
	StructuredBuffer perTriangleBuffer;
	RWBuffer headBuffer;
	RWBuffer listLengthBuffer;
	RWBuffer offsetBuffer;
	RWBuffer histogramCount;
	ID3D11BufferPtr stagingBuffer;
	ID3D11BufferPtr stagingBufferBig;
	StructuredBuffer triangleIntersect;
    StructuredBuffer tailBuffer;

	StructuredBuffer headBufferNew;
	StructuredBuffer tailBufferNew;

};