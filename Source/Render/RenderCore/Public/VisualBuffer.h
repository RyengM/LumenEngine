#pragma once

#include "Render/RHI/Common/Public/RHIResourceView.h"
#include <string>
#include <memory>
#include <iostream>

namespace Lumen::Render
{
    // Buffer with gpu handle, used for display in gui
    struct VisualBuffer
    {
        VisualBuffer(std::string_view name) : name(name) {};
        ~VisualBuffer() { std::cout << "release" << std::endl; };

        std::string name;
        // Gpu handle
        uint64_t srvHandle = 0;
        uint64_t rtvHandle = 0;

        std::unique_ptr<RHIRenderTargetView> rtv;
        std::unique_ptr<RHIShaderResourceView> srv;
    };
}