#pragma once

#include "RHIDevice.h"
#include "RHIResourceView.h"
#include "RHICommandContext.h"
#include "RHIDescriptorHeap.h"
#include <string>

using namespace Lumen::Core;

namespace Lumen::Render
{
    class RHICommandBuffer
    {
    public:
        virtual void Clear() = 0;

        virtual void Close() = 0;

        virtual void ClearRenderTarget(RHITexture* texture, RHIRenderTargetView* rtvView, const Vec4& color) = 0;

        virtual void DrawUI(RHIDescriptorHeap* rhiHeap, RHITexture* texture, RHIRenderTargetView* rtvView, void* data) = 0;

    protected:
        std::string name;
        EContextType contextType;
        // CmdList will be closed when initialized
        bool bClose = true;
    };

    class RHICommandBufferPool
    {

    };
}