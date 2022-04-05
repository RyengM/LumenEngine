#pragma once

#include "Game/Asset/Public/ShaderLabCompiler.h"
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
        std::vector<std::shared_ptr<AssetTreeNode>> children;

        AssetTreeNode() = default;
        AssetTreeNode(int depth, std::string_view name, std::string_view path, std::string_view type) :
            depth(depth), fileName(name), filePath(path), fileType(type) {}
    };

    class AssetManager
    {
    public:
        AssetManager();
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;
        // Release allocated data and return view to memory pool, do later
        ~AssetManager() {}

        bool LoadAsset(std::filesystem::path path);
        // Scan assets folder, buuid asset tree and resource map
        void BuildResourceMap();

        Mesh* GetMeshByGUID(xg::Guid guid);
        Texture* GetTextureByGUID(xg::Guid guid);
        ShaderLab* GetShaderlabByGUID(xg::Guid guid);
        
        inline Scene* GetScene() noexcept { return mScene.get(); }
        inline AssetTreeNode* GetAssetTree() noexcept { return mAssetTree.get(); }

    private:
        void EnterDictRecur(const std::string& dir, AssetTreeNode* node);

    private:
        // There can be only one scene at one time
        std::unique_ptr<Scene> mScene;
        // Asset tree
        std::unique_ptr<AssetTreeNode> mAssetTree;

        // ID-Resource map with original pointer
        std::unordered_map<xg::Guid, Mesh*> mGuid2MeshMap;
        std::unordered_map<xg::Guid, Texture*> mGuid2TextureMap;
        std::unordered_map<xg::Guid, Material*> mGuid2MaterialMap;
        std::unordered_map<xg::Guid, ShaderLab*> mGuid2ShaderLabMap;

        // Resource memory pool
        MemoryPool<Mesh> mMeshStorage;
        MemoryPool<Texture> mTextureStorage;
        MemoryPool<Material> mMaterialStorage;
        MemoryPool<ShaderLab> mShaderLabStorage;
    };
}