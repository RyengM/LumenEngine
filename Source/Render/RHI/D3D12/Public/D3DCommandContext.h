#pragma once

#include "D3DFence.h"
#include "D3DFrameResource.h"
#include "Render/RHI/Common/Public/RHICommandBuffer.h"

namespace Lumen::Render
{
    // We assume there is only graphics context now, may be expanded later
    class D3DCommandContext : public RHICommandContext
    {
    public:
        D3DCommandContext(RHIDevice* rhiDevice, EContextType type, std::string_view name);

    public:
        //virtual void ExecuteQueue(RHICommandBuffer* cmdBuffer) override;

        virtual void BeginFrame() override;

        virtual void EndFrame() override;

        virtual void FlushQueue() override;

    public:
        Microsoft::WRL::ComPtr<ID3D12CommandQueue>          commandQueue;
        std::vector<std::unique_ptr<D3DFrameResource>>      frameResource;
        D3DFrameResource*                                   currentFrameResource;
        size_t                                              currentFrameResourceIndex = 0;

        std::unique_ptr<D3DFence>                           fence;
    };
}