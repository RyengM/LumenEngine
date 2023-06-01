#pragma once

#include "Game/Asset/Public/Scene.h"
#include "Game/Asset/Public/Mesh.h"
#include "Game/Asset/Public/Texture.h"
#include "Game/Asset/Public/Material.h"
#include "Game/Asset/Public/Meta.h"
#include "Core/Memory/Public/MemoryPool.h"
#include "Core/Common/Public/Guid.hpp"
#include <filesystem>

namespace Lumen::Game
{
    struct AssetTreeNode
    {
        int depth;
        std::string fileName;
        std::string filePath;
        std::string fileType;
        std::string fileGuid;
        std::vector<std::shared_ptr<AssetTreeNode>> children;

        AssetTreeNode() = default;
        AssetTreeNode(int depth, std::string_view name, std::string_view path, std::string_view type) :
            depth(depth), fileName(name), filePath(path), fileType(type) {}
    };

    class AssetManager
    {
    public:
        static AssetManager& GetInstance();

        bool LoadAsset(std::filesystem::path path);
        // Scan assets folder, buuid asset tree and resource map
        void BuildResourceMap();
        // Serialize scene to asset folder, TODO, now only support one default scene
        void SaveScene();

        // Create material asset
        void CreateMaterial(const xg::Guid& guid);

        Mesh* GetMeshByGUID(xg::Guid guid);
        Texture* GetTextureByGUID(xg::Guid guid);
        Material* GetMaterialByGUID(xg::Guid guid);
        ShaderLab* GetShaderlabByGUID(xg::Guid guid);
        ShaderLab* GetDefaultShaderlab();
        
        inline Scene* GetScene() noexcept { return mScene.get(); }
        inline AssetTreeNode* GetAssetTree() noexcept { return mAssetTree.get(); }
        inline std::unordered_map<std::string, Mesh*>* GetBuiltInMeshMap() noexcept { return &mBuiltInMeshMap; }

    private:
        AssetManager();
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;
        // Release allocated data and return view to memory pool, do later
        ~AssetManager() {}

        void EnterDictRecur(const std::string& dir, AssetTreeNode* node);
        void CreateBuiltInMeshes();

    private:
        // There can be only one scene at one time
        std::unique_ptr<Scene> mScene;
        // Asset tree
        std::unique_ptr<AssetTreeNode> mAssetTree;

        // ID-Resource map with original pointer
        std::map<xg::Guid, Mesh*> mGuid2MeshMap;
        std::map<xg::Guid, Texture*> mGuid2TextureMap;
        std::map<xg::Guid, Material*> mGuid2MaterialMap;
        std::map<xg::Guid, ShaderLab*> mGuid2ShaderLabMap;

        // Built-in meshes
        std::unordered_map<std::string, Mesh*> mBuiltInMeshMap;

        // Resource memory pool
        MemoryPool<Mesh> mMeshStorage;
        MemoryPool<Texture> mTextureStorage;
        MemoryPool<Material> mMaterialStorage;
        MemoryPool<ShaderLab> mShaderLabStorage;

        // The index is used for avoiding name duplication
        // TODO. use a better way to manage index to avoid name duplication
        uint32_t matIndex = 0;

        // Default shaderlab guid to initialize default material
        xg::Guid mDefaultShaderGuid;
    };
}