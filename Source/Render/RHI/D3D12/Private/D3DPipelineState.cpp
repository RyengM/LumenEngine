#include "Render/RHI/D3D12/Public/D3DPipelineState.h"
#include "Render/RHI/D3D12/Public/D3DShader.h"

using namespace Lumen::Render;

D3D12_CULL_MODE GetCullMode(ECullMode mode)
{
	if (mode == ECullMode::Back)
		return D3D12_CULL_MODE_BACK;
	else if (mode == ECullMode::Front)
		return D3D12_CULL_MODE_FRONT;
	
	return D3D12_CULL_MODE_NONE;
}

std::array<const CD3DX12_STATIC_SAMPLER_DESC, 7> GetStaticSamplers()
{
	// Applications usually only need a handful of samplers.  So just define them all up front
	// and keep them available as part of the root signature.  

	const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
		0, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC pointClamp(
		1, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearWrap(
		2, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearClamp(
		3, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicWrap(
		4, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
		0.0f,                             // mipLODBias
		8);                               // maxAnisotropy

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicClamp(
		5, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
		0.0f,                              // mipLODBias
		8);                                // maxAnisotropy

	const CD3DX12_STATIC_SAMPLER_DESC shadow(
		6, // shaderRegister
		D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressW
		0.0f,                               // mipLODBias
		16,                                 // maxAnisotropy
		D3D12_COMPARISON_FUNC_LESS_EQUAL,
		D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK);

	return {
		pointWrap, pointClamp,
		linearWrap, linearClamp,
		anisotropicWrap, anisotropicClamp,
		shadow
	};
}

D3DPipelineState::D3DPipelineState(RHIDevice* rhiDevice, std::string_view name, Kernel* shaderlabKernel, RHIShader* rhiShader) : name(name)
{
	D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);
	D3DShader* shader = static_cast<D3DShader*>(rhiShader);

	// Fix input layout and rootsignature here, be removed later
	inputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TANGENTU", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	CD3DX12_DESCRIPTOR_RANGE texTable0;
	texTable0.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 3, 0, 0);
	CD3DX12_DESCRIPTOR_RANGE texTable1;
	texTable1.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 3, 0);
	CD3DX12_ROOT_PARAMETER slotRootParameter[4];
	slotRootParameter[0].InitAsConstantBufferView(0);
	slotRootParameter[1].InitAsConstantBufferView(1);
	slotRootParameter[2].InitAsDescriptorTable(1, &texTable0, D3D12_SHADER_VISIBILITY_PIXEL);
	slotRootParameter[3].InitAsDescriptorTable(1, &texTable1, D3D12_SHADER_VISIBILITY_PIXEL);

	auto staticSamplers = GetStaticSamplers();
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(4, slotRootParameter, (UINT)staticSamplers.size(), staticSamplers.data(), D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	//CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(4, slotRootParameter, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	
	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	Microsoft::WRL::ComPtr<ID3DBlob> serializedRootSig = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());
	if (errorBlob != nullptr)
	{
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);

	ThrowIfFailed(device->d3dDevice->CreateRootSignature(0, serializedRootSig->GetBufferPointer(), serializedRootSig->GetBufferSize(), IID_PPV_ARGS(&rootSignature)));

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

    ZeroMemory(&psoDescriptor, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDescriptor.InputLayout = { inputLayout.data(), (UINT)inputLayout.size() };
	psoDescriptor.pRootSignature = rootSignature.Get();
	psoDescriptor.VS =
	{
		reinterpret_cast<BYTE*>(shader->vertexShader->GetBufferPointer()),
		shader->vertexShader->GetBufferSize()
	};
	psoDescriptor.PS =
	{
		reinterpret_cast<BYTE*>(shader->pixelShader->GetBufferPointer()),
		shader->pixelShader->GetBufferSize()
	};
	psoDescriptor.RasterizerState = rasterizerDescriptor;
	psoDescriptor.BlendState = blendDescriptor;
	psoDescriptor.DepthStencilState = depthStencilDescriptor;
	psoDescriptor.SampleMask = UINT_MAX;
	psoDescriptor.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDescriptor.NumRenderTargets = 1;
	psoDescriptor.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDescriptor.SampleDesc.Count = 1;
	psoDescriptor.SampleDesc.Quality = 0;
	psoDescriptor.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	ThrowIfFailed(device->d3dDevice->CreateGraphicsPipelineState(&psoDescriptor, IID_PPV_ARGS(&d3dPso)));
}