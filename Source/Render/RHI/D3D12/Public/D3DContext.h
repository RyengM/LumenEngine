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
    enum class ERenderLayer : uint32_t
    {
        Opaque  = 0,
        Sky     = 1,
        Count   = 2
    };

    class D3DContext : public RHIContext
    {
    public:
        D3DContext(const WindowInfo& windowInfo);

    public:
        virtual void BeginFrame() override;

        virtual void EndFrame() override;

        virtual RHICommandBuffer* RequestCmdBuffer(const EContextType& type, std::string_view name) override;

        virtual void ReleaseCmdBuffer(RHICommandBuffer* cmdBuffer) override;

        virtual void ExecuteCmdBuffer(RHICommandBuffer* cmdBuffer) override;

        virtual void Present() override;

        virtual void UpdateObjectCB(const Entity& entity) override;

        virtual void UpdatePassCB(const Camera& camera, const DirectionalLight& light) override;

        virtual void RenderScene(uint32_t width, uint32_t height) override;

        virtual void DrawUI(void* data) override;

        virtual void CreateSceneBuffer(VisualBuffer* buffer) override;

        virtual void CreatePlainTexture(Texture& texture) override;

        virtual void CreateCubeMap(std::vector<Texture>& textures) override;

        virtual void CreateGeometry(const Mesh& mesh) override;

        virtual void CreateShaderlab(const ShaderLab& shaderlab) override;

        virtual void CreateRenderItem(const Entity& entity) override;

        virtual void CreateSkyItem() override;

        virtual RHICommandContext* GetContext(const EContextType& type) override;

    private:
        void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<D3DRenderItem*>& renderItems);

    private:
        std::unique_ptr<D3DDevice>                          mDevice;

        std::unique_ptr<D3DSwapChain>                       mSwapChain;

        std::unique_ptr<D3DCommandBufferPool>               mGraphicsBufferPool;
        std::unique_ptr<D3DCommandContext>                  mGraphicsContext;

        std::unique_ptr<D3DDepthRenderTarget>               mSceneRT;

        std::unique_ptr<D3DDescriptorHeap>                  mCbvSrvUavDescriptorHeap;
        std::unique_ptr<D3DDescriptorHeap>                  mRtvDescriptorHeap;
        std::unique_ptr<D3DDescriptorHeap>                  mDsvDescriptorHeap;
        std::unique_ptr<D3DDescriptorHeap>                  mSamplerDescriptorHeap;

        std::unordered_map<std::string, std::unique_ptr<D3DPlainTexture>>       mTextures;
        std::unordered_map<std::string, std::unique_ptr<D3DMeshGeometry>>       mMeshes;
        std::unordered_map<std::string, std::unique_ptr<D3DMaterial>>           mMaterials;
        std::unordered_map<std::string, std::unique_ptr<D3DShader>>             mShaders;
        std::unordered_map<std::string, std::unique_ptr<D3DPipelineState>>      mPSOs;
        std::unordered_map<std::string, std::unique_ptr<D3DRenderItem>>         mAllRenderItems;
        std::vector<D3DRenderItem*>                                             mRenderItems[(uint32_t)ERenderLayer::Count];

        UINT                                                                    mIncreRenderItemIndex = 0;
    };
}