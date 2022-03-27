#pragma once

#include "RHIDescriptorHeap.h"
#include "RHIResourceView.h"
#include "RHIShader.h"
#include "RHICommandBuffer.h"
#include "RHISwapChain.h"
#include "Render/RenderCore/Public/VisualBuffer.h"
#include "Game/Asset/Public/ShaderLab.h"
#include "Game/Asset/Public/Mesh.h"
#include "Game/GamePlay/Public/Camera.h"
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

        virtual RHICommandBuffer* RequestCmdBuffer(const EContextType& type, std::string_view name) = 0;

        virtual void ReleaseCmdBuffer(RHICommandBuffer* cmdBuffer) = 0;

        virtual void ExecuteCmdBuffer(RHICommandBuffer* cmdBuffer) = 0;

        virtual void Present() = 0;

        virtual void Prepare() = 0;

        virtual void UpdatePassCB(const Camera& camera) = 0;

        virtual void RenderScene() = 0;

        // Create texture both with srv and rtv for display convenience
        virtual void CreateVisualBuffer(VisualBuffer* buffer) = 0;

        // Create geometry
        virtual void CreateGeometry(RHICommandBuffer* cmdBuffer, const Mesh& mesh) = 0;

        // Create shaders
        virtual void CreateShaders(const ShaderLab& shaderlab) = 0;

        virtual RHICommandContext* GetContext(const EContextType& type) = 0;

        virtual RHIDescriptorHeap* GetDescriptorHeap(const EHeapDescriptorType& type) = 0;

        virtual RHIRenderTargetView* GetBackBufferView() = 0;

        virtual RHITexture* GetBackBuffer() = 0;

        virtual RHIDepthStencilView* GetBackDepthStencilView() = 0;
    };
}