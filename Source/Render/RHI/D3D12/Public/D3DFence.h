#pragma once

#include "D3DDevice.h"
#include "Render/RHI/Common/Public/RHICommandContext.h"
#include "Render/RHI/Common/Public/RHIFence.h"

namespace Lumen::Render
{
    class D3DFence : public RHIFence
    {
    public:
        D3DFence(RHIDevice* rhiDevice, std::string_view name);

        virtual void Signal(RHICommandContext* rhiContext) override;

    public:
        Microsoft::WRL::ComPtr<ID3D12Fence>                 d3dFence;
        UINT64                                              currentFenceValue = 0;
    };
}