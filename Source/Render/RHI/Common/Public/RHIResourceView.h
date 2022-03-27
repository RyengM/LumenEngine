#pragma once

#include "RHIResource.h"

namespace Lumen::Render
{
    class RHIResourceView
    {
    public:
        int offset;
        size_t gpuAddress;
    };

    class RHIRenderTargetView : public RHIResourceView
    {

    };

    class RHIDepthStencilView : public RHIResourceView
    {

    };

    class RHIShaderResourceView : public RHIResourceView
    {

    };
}