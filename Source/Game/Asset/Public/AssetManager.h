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
    class AssetManager
    {
    public:
        AssetManager();
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;
        // Release allocated data and return view to memory pool, do later
        ~AssetManager() {}

        bool LoadAsset(std::filesystem::path path);
        // Scan assets folder and build resource map
        void BuildResourceMap();

        Mesh* GetMeshByGUID(xg::Guid guid);
        Texture* GetTextureByGUID(xg::Guid guid);
        ShaderLab* GetShaderlabByGUID(xg::Guid guid);
        
        inline Scene* GetScene() noexcept { return mScene.get(); }

    private:
        void EnterDictRecur(const std::string& dir);

    private:
        // There can be only one scene at one time
        std::unique_ptr<Scene> mScene;

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