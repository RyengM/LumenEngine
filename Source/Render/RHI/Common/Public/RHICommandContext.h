#pragma once

//#include "RHICommandBuffer.h"
#include <string>

namespace Lumen::Render
{
    enum class EContextType : uint32_t
    {
        Copy = 3,
        Compute = 2,
        Graphics = 0
    };

    class RHICommandContext
    {
    public:
        virtual void BeginFrame() = 0;

        virtual void EndFrame() = 0;

        virtual void FlushQueue() = 0;

    public:
        std::string name;
        int numFrameResource = 3;
    };
}