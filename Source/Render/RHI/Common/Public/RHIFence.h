#pragma once

#include "RHICommandContext.h"

namespace Lumen::Render
{
    class RHIFence
    {
    public:
        virtual void Signal(RHICommandContext* context) = 0;

    public:
        std::string name;
    };
}