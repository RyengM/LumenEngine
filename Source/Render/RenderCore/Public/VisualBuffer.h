#pragma once

#include "Render/RHI/Common/Public/RHIResourceView.h"
#include <string>
#include <memory>

namespace Lumen::Render
{
    // Buffer with gpu handle, used for display in gui
    struct VisualBuffer
    {
        VisualBuffer(std::string_view name, uint32_t width, uint32_t height) : name(name), width(width), height(height) {};
        ~VisualBuffer() {};

        std::string name;

        uint32_t width;
        uint32_t height;

        // Gpu handle
        uint64_t srvHandle;
    };
}