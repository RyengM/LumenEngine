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
        static AssetManager& GetInstance();

        bool LoadAsset(std::filesystem::path path);

    private:
        AssetManager() {};
        ~AssetManager() {};
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;

    private:
        // There can be only one scene at one time
        std::unique_ptr<Scene> mScene;

        // ID-Resource map with original pointer
        std::unordered_map<xg::Guid, Mesh*> mGuid2MeshMap;
        std::unordered_map<xg::Guid, Texture*> mGuid2TextureMap;
        std::unordered_map<xg::Guid, Material*> mGuid2MaterialMap;
        std::unordered_map<xg::Guid, ShaderLab*> mGuid2ShaderLabMap;

        // Shared memory storage, use shared_ptr with custom deleter to manage resource
        MemoryPool<Mesh> mMeshStorage;
        MemoryPool<Texture> mTextureStorage;
        MemoryPool<Material> mMaterialStorage;
        MemoryPool<ShaderLab> mShaderLabStorage;
    };
}