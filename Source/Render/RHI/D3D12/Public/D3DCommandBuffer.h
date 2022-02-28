#pragma once

#include "D3DCommandContext.h"
#include "D3DResourceView.h"
#include "Render/RHI/Common/Public/RHICommandBuffer.h"

namespace Lumen::Render
{
    class D3DCommandBuffer : public RHICommandBuffer
    {
    public:
        D3DCommandBuffer(RHIDevice* rhiDevice, RHICommandContext* rhiContext, EContextType contextType);

    public:
        virtual void Close() override;

        virtual void Clear() override;

        virtual void ClearRenderTarget(RHITexture* texture, RHIRenderTargetView* rtvView, const Vec4& color) override;

        virtual void DrawUI(RHIDescriptorHeap* rhiHeap, RHITexture* texture, RHIRenderTargetView* rtvView, void* data) override;

    public:
        size_t                                                  indexInPool;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>       commandList;
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator>          commandAllocator;
    };

    class D3DCommandBufferPool : public RHICommandBufferPool
    {
    public:
        D3DCommandBufferPool(RHIDevice* rhiDevice, RHICommandContext* rhiContext, EContextType inContextType, size_t capacity);

        D3DCommandBuffer* RequestElement(std::string_view name);
        void ReturnElement(D3DCommandBuffer* cmdBuffer);

    private:
        void Expand();

    private:
        D3DCommandContext* ownerContext;
        std::vector<D3DCommandBuffer> mCmdBuffers;
        std::vector<size_t> mFreeElements;
    };
}