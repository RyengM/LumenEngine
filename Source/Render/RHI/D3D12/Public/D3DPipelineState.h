#pragma once

#include "D3DDevice.h"
#include "Render/RHI/Common/Public/RHIPipelineState.h"
#include "Render/RHI/Common/Public/RHIShader.h"
#include "Game/Asset/Public/ShaderLab.h"

using namespace Lumen::Game;

namespace Lumen::Render
{
    class D3DPipelineState : public RHIPipelineState
    {
    public:
        D3DPipelineState(RHIDevice* rhiDevice, std::string_view name, Kernel* shaderlabKernel, RHIShader* rhiShader);

    public:
        std::string                                         name;
        Microsoft::WRL::ComPtr<ID3D12PipelineState>         d3dPso = nullptr;
        Microsoft::WRL::ComPtr<ID3D12RootSignature>         rootSignature;
        std::vector<D3D12_INPUT_ELEMENT_DESC>               inputLayout;
    };
}