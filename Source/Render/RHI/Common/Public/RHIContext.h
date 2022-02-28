#pragma once

#include "RHIDescriptorHeap.h"
#include "RHIResourceView.h"
#include "RHIShader.h"
#include "RHICommandBuffer.h"
#include "RHISwapChain.h"
#include "Game/Asset/Public/Mesh.h"
#include <memory>

using namespace Lumen::Game;

namespace Lumen::Render
{
    struct WindowInfo
    {
        void*               mainWnd = nullptr;
        int                 clientWidth = 1920;
        int                 clientHeight = 1080;
    };

    class RHIContext
    {
    public:
        // Switch frame resource and wait for gpu fence
        virtual void BeginFrame() = 0;

        // Signal fence and reset allocator
        virtual void EndFrame() = 0;

        virtual RHICommandContext* GetContext(const EContextType& type) = 0;

        virtual RHIDescriptorHeap* GetDescriptorHeap(const EHeapDescriptorType& type) = 0;

        virtual RHICommandBuffer* RequestCmdBuffer(const EContextType& type, std::string_view name) = 0;

        virtual void ReleaseCmdBuffer(RHICommandBuffer* cmdBuffer) = 0;

        virtual void ExecuteCmdBuffer(RHICommandBuffer* cmdBuffer) = 0;

        virtual RHIRenderTargetView* GetBackBufferView() = 0;

        virtual RHITexture* GetBackBuffer() = 0;

        virtual void Present() = 0;

        virtual void CreateGeometry(Mesh* mesh) = 0;
    };
}