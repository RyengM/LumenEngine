#pragma once

#include "RHICommandBuffer.h"
#include <string>

namespace Lumen::Render
{
    class RHICommandContext
    {
    public:
        virtual void ExecuteQueue(RHICommandBuffer* cmdBuffer) = 0;

        virtual void BeginFrame() = 0;

        virtual void EndFrame() = 0;

        virtual void FlushQueue() = 0;

    public:
        std::string name;
        static const int numFrameResource = 3;
    };
}