#pragma once

#include "D3DDescriptorHeap.h"
#include "D3DResource.h"
#include "D3DShader.h"
#include "D3DCommandBuffer.h"
#include "D3DSwapChain.h"
#include "D3DPipelineState.h"
#include "Render/RHI/Common/Public/RHIContext.h"

namespace Lumen::Render
{
    class D3DContext : public RHIContext
    {
    public:
        D3DContext(const WindowInfo& windowInfo);

    public:
        virtual void BeginFrame() override;

        virtual void EndFrame() override;

        virtual RHICommandContext* GetContext(const EContextType& type) override;

        virtual RHIDescriptorHeap* GetDescriptorHeap(const EHeapDescriptorType& type) override;

        virtual RHICommandBuffer* RequestCmdBuffer(const EContextType& type, std::string_view name) override;

        virtual void ReleaseCmdBuffer(RHICommandBuffer* cmdBuffer) override;

        virtual void ExecuteCmdBuffer(RHICommandBuffer* cmdBuffer) override;

        virtual RHIRenderTargetView* GetBackBufferView() override;

        virtual RHITexture* GetBackBuffer() override;

        virtual void Present() override;

        virtual void CreateGeometry(Mesh* mesh) override;

    private:
        std::unique_ptr<D3DDevice>                          mDevice;

        std::unique_ptr<D3DSwapChain>                       mSwapChain;

        std::unique_ptr<D3DCommandBufferPool>               mGraphicsBufferPool;
        std::unique_ptr<D3DCommandContext>                  mGraphicsContext;

        std::unique_ptr<D3DDescriptorHeap>                  mCbvSrvUavDescriptorHeap;
        std::unique_ptr<D3DDescriptorHeap>                  mRtvDescriptorHeap;
        std::unique_ptr<D3DDescriptorHeap>                  mDsvDescriptorHeap;
        std::unique_ptr<D3DDescriptorHeap>                  mSamplerDescriptorHeap;

        std::unordered_map<std::string, std::unique_ptr<D3DTexture>>            mTextures;
        std::unordered_map<std::string, std::unique_ptr<D3DMeshGeometry>>       mMeshes;
        std::unordered_map<std::string, std::unique_ptr<D3DMaterial>>           mMaterials;
        std::unordered_map<std::string, std::unique_ptr<D3DPipelineState>>      mPSOs;
    };
}