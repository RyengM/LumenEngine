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
        // Switch frame resource and wait for gpu fence
        virtual void BeginFrame() override;

        // Signal fence and reset allocator
        virtual void EndFrame() override;

        virtual RHICommandBuffer* RequestCmdBuffer(const EContextType& type, std::string_view name) override;

        virtual void ReleaseCmdBuffer(RHICommandBuffer* cmdBuffer) override;

        virtual void ExecuteCmdBuffer(RHICommandBuffer* cmdBuffer) override;

        virtual void Present() override;

        virtual void UpdateObjectCB(const Entity& entity) override;

        virtual void UpdatePassCB(const Camera& camera, const DirectionalLight& light) override;

        virtual void UpdateMaterialCB(const Material& mat) override;

        virtual void RenderScene(uint32_t width, uint32_t height) override;

        virtual void DrawUI(void* data) override;

        // Create scene buffer for display
        virtual void CreateSceneBuffer(VisualBuffer* buffer) override;

        // Create all GPU resources related to entity
        virtual void CreateEntity(const Entity& entity, const MeshComponent& meshContainer, const MeshRendererComponent& meshRenderer) override;

        // Update all GPU resources related to entity
        virtual void UpdateEntity(const Entity& entity, const MeshComponent& meshContainer, const MeshRendererComponent& meshRenderer) override;

        // Create texture
        virtual void CreatePlainTexture(Texture* texture, std::string_view guid) override;

        // Create cubemap
        virtual void CreateCubeMap(std::vector<Texture>& textures) override;

        // Create geometry
        virtual void CreateGeometry(Mesh* mesh, std::string_view guid) override;

        // Create material, return offset of material constant buffer, not consider material remove yet
        virtual uint32_t CreateMaterial(Material* mat, std::string_view guid) override;

        // Create geometry directly, make sure mesh is static
        virtual void CreateGeometry(const Mesh& mesh, std::string_view guid) override;

        // Create shaders
        virtual void CreateShaderlab(const ShaderLab& shaderlab) override;

        // Create render item
        virtual void CreateRenderItem(const Entity& entity, const MeshComponent& meshContainer, const MeshRendererComponent& meshRenderer) override;

        // Update render item resource bind
        virtual void UpdateRenderItem(const Entity& entity, const MeshComponent& meshContainer, const MeshRendererComponent& meshRenderer) override;

        // Remove render item
        virtual void RemoveRenderItem(std::string_view guid) override;

        // Create sky render item
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

        // Param: std::string
        // -- texture mesh renderItem: guid
        // -- pso shader builtinMesh : name
        std::unordered_map<std::string, std::unique_ptr<D3DPlainTexture>>       mTextures;
        std::unordered_map<std::string, std::unique_ptr<D3DMeshGeometry>>       mMeshes;
        std::unordered_map<std::string, std::unique_ptr<D3DMaterial>>           mMaterials;
        std::unordered_map<std::string, std::unique_ptr<D3DShader>>             mShaders;
        std::unordered_map<std::string, std::unique_ptr<D3DPipelineState>>      mPSOs;
        std::unordered_map<std::string, std::unique_ptr<D3DRenderItem>>         mAllRenderItems;
        std::vector<D3DRenderItem*>                                             mRenderItems[(uint32_t)ERenderLayer::Count];

        // Need more flexible pattern later
        UINT                                                                    mIncreRenderItemIndex = 0;
        uint32_t                                                                mIncreMaterialOffset = 0;
    };
}