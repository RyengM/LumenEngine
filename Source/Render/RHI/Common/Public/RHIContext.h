#pragma once

#include "RHIDescriptorHeap.h"
#include "RHIResourceView.h"
#include "RHIShader.h"
#include "RHICommandBuffer.h"
#include "RHISwapChain.h"
#include "Render/RenderCore/Public/VisualBuffer.h"
#include "Game/Asset/Public/Scene.h"
#include "Game/Asset/Public/ShaderLab.h"
#include "Game/Asset/Public/Mesh.h"
#include "Game/Asset/Public/Texture.h"
#include "Game/GamePlay/Public/Camera.h"
#include "Game/GamePlay/Public/Light.h"
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

    struct ProfileData
    {
        float               gameThreadTickTime;
        float               renderThreadTickTime;
    };

    class RHIContext
    {
    public:
        virtual void BeginFrame() = 0;

        virtual void EndFrame() = 0;

        virtual RHICommandBuffer* RequestCmdBuffer(const EContextType& type, std::string_view name) = 0;

        virtual void ReleaseCmdBuffer(RHICommandBuffer* cmdBuffer) = 0;

        virtual void ExecuteCmdBuffer(RHICommandBuffer* cmdBuffer) = 0;

        virtual void Present() = 0;

        virtual void UpdateObjectCB(const Entity& entity) = 0;

        virtual void UpdatePassCB(const Camera& camera, const DirectionalLight& light) = 0;

        virtual void UpdateMaterialCB(const Material& mat) = 0;

        virtual void RenderScene(uint32_t width, uint32_t height) = 0;

        virtual void DrawUI(void* data) = 0;

        virtual void CreateSceneBuffer(VisualBuffer* buffer) = 0;

        virtual void CreateEntity(const Entity& entity, const MeshComponent& meshContainer, const MeshRendererComponent& meshRenderer) = 0;

        virtual void UpdateEntity(const Entity& entity, const MeshComponent& meshContainer, const MeshRendererComponent& meshRenderer) = 0;

        virtual void CreateGeometry(const Mesh& mesh, std::string_view guid) = 0;

        virtual void CreateShaderlab(const ShaderLab& shaderlab) = 0;

        virtual void RemoveRenderItem(std::string_view guid) = 0;

        virtual void CreateSkyItem() = 0;

        virtual RHICommandContext* GetContext(const EContextType& type) = 0;

    protected:
        virtual void CreatePlainTexture(Texture* texture, std::string_view guid) = 0;

        virtual void CreateCubeMap(std::vector<Texture>& textures) = 0;

        virtual void CreateGeometry(Mesh* mesh, std::string_view guid) = 0;

        virtual uint32_t CreateMaterial(Material* mat, std::string_view guid) = 0;

        virtual void CreateRenderItem(const Entity& entity, const MeshComponent& meshContainer, const MeshRendererComponent& meshRenderer) = 0;

        virtual void UpdateRenderItem(const Entity& entity, const MeshComponent& meshContainer, const MeshRendererComponent& meshRenderer) = 0;
    };
}