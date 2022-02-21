#pragma once

#include "D3DDevice.h"
#include "Render/RHI/Common/Public/RHIPipelineState.h"
//#include "Game/Asset/Public/ShaderLab.h"
//
//using namespace Lumen::Game;

namespace Lumen::Render
{
    class D3DPipelienState : public RHIPipelineState
    {
    public:
        //D3DPipelienState(RHIDevice* rhiDevice, std::string_view name, ShaderLab* shaderlab);
        D3DPipelienState() {};

    private:
        std::string                                         mName;
        Microsoft::WRL::ComPtr<ID3D12PipelineState>         mPSO = nullptr;
        std::vector<D3D12_INPUT_ELEMENT_DESC>               mInputLayout;
    };
}