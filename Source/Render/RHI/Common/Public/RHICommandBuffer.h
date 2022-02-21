#pragma once

#include "RHIDevice.h"
#include "RHIResourceView.h"
#include <string>

using namespace Lumen::Core;

namespace Lumen::Render
{
    enum class EContextType : uint32_t
    {
        Copy = 3,
        Compute = 2,
        Graphics = 0
    };

    class RHICommandBuffer
    {
    public:
        virtual void Clear() = 0;

        virtual void Close() = 0;

        virtual void ClearRenderTarget(RHITexture* texture, RHIRenderTargetView* rtvView, const Vec4& color) = 0;

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