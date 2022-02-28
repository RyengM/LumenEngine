#pragma once

#include "D3DDevice.h"
#include "Render/RHI/Common/Public/RHIPipelineState.h"
#include "Game/Asset/Public/ShaderLab.h"

using namespace Lumen::Game;

namespace Lumen::Render
{
    class D3DPipelineState : public RHIPipelineState
    {
    public:
        D3DPipelineState(RHIDevice* rhiDevice, std::string_view name, Kernel* shaderlabKernel);

    private:
        std::string                                         mName;
        Microsoft::WRL::ComPtr<ID3D12PipelineState>         mPSO = nullptr;
        Microsoft::WRL::ComPtr<ID3D12RootSignature>         mRootSignature;
        std::vector<D3D12_INPUT_ELEMENT_DESC>               mInputLayout;
    };
}