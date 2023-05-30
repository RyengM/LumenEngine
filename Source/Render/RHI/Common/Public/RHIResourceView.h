#pragma once

#include "RHIResource.h"

namespace Lumen::Render
{
    class RHIResourceView
    {
    public:
        int offset;
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