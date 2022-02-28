#include "Render/RHI/D3D12/Public/D3DPipelineState.h"

using namespace Lumen::Render;

D3D12_CULL_MODE GetCullMode(ECullMode mode)
{
	if (mode == ECullMode::Back)
		return D3D12_CULL_MODE_BACK;
	else if (mode == ECullMode::Front)
		return D3D12_CULL_MODE_FRONT;
	
	return D3D12_CULL_MODE_NONE;
}

D3DPipelineState::D3DPipelineState(RHIDevice* rhiDevice, std::string_view name, Kernel* shaderlabKernel) : mName(name)
{
	D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);

	// Need to be adjusted by shaderlab config later
	D3D12_RASTERIZER_DESC rasterizerDescriptor;
	{
		rasterizerDescriptor.FillMode = D3D12_FILL_MODE_SOLID;
		rasterizerDescriptor.CullMode = GetCullMode(shaderlabKernel->commonState.cullMode);
		rasterizerDescriptor.FrontCounterClockwise = FALSE;
		rasterizerDescriptor.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
		rasterizerDescriptor.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		rasterizerDescriptor.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		rasterizerDescriptor.DepthClipEnable = TRUE;
		rasterizerDescriptor.MultisampleEnable = FALSE;
		rasterizerDescriptor.AntialiasedLineEnable = FALSE;
		rasterizerDescriptor.ForcedSampleCount = 0;
		rasterizerDescriptor.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	}

	D3D12_BLEND_DESC blendDescriptor;
	{
		blendDescriptor.AlphaToCoverageEnable = FALSE;
		blendDescriptor.IndependentBlendEnable = FALSE;
		const D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc =
		{
			FALSE,FALSE,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_LOGIC_OP_NOOP,
			D3D12_COLOR_WRITE_ENABLE_ALL,
		};
		for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
			blendDescriptor.RenderTarget[i] = defaultRenderTargetBlendDesc;
	}

	D3D12_DEPTH_STENCIL_DESC depthStencilDescriptor;
	{
		depthStencilDescriptor.DepthEnable = TRUE;
		depthStencilDescriptor.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		depthStencilDescriptor.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
		depthStencilDescriptor.StencilEnable = FALSE;
		depthStencilDescriptor.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
		depthStencilDescriptor.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
		const D3D12_DEPTH_STENCILOP_DESC defaultStencilOp = 
			{ D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS };
		depthStencilDescriptor.FrontFace = defaultStencilOp;
		depthStencilDescriptor.BackFace = defaultStencilOp;
	}

    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDescriptor;

 //   ZeroMemory(&psoDescriptor, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	//psoDescriptor.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
	//psoDescriptor.pRootSignature = mRootSignature.Get();
	//psoDescriptor.VS =
	//{
	//	reinterpret_cast<BYTE*>(mShaders["standardVS"]->GetBufferPointer()),
	//	mShaders["standardVS"]->GetBufferSize()
	//};
	//psoDescriptor.PS =
	//{
	//	reinterpret_cast<BYTE*>(mShaders["opaquePS"]->GetBufferPointer()),
	//	mShaders["opaquePS"]->GetBufferSize()
	//};
	//psoDescriptor.RasterizerState = rasterizerDescriptor;
	//psoDescriptor.BlendState = blendDescriptor;
	//psoDescriptor.DepthStencilState = depthStencilDescriptor;
	//psoDescriptor.SampleMask = UINT_MAX;
	//psoDescriptor.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//psoDescriptor.NumRenderTargets = 1;
	//psoDescriptor.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	//psoDescriptor.SampleDesc.Count = 1;
	//psoDescriptor.SampleDesc.Quality = 0;
	//psoDescriptor.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//ThrowIfFailed(device->d3dDevice->CreateGraphicsPipelineState(&psoDescriptor, IID_PPV_ARGS(&mPSO)));
}