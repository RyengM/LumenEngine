#include "Game/Asset/Public/AssetManager.h"
#include "Game/Asset/Public/Serializer.h"

using namespace Lumen::Game;

AssetManager& AssetManager::GetInstance()
{
    static AssetManager instance;
    return instance;
}

bool AssetManager::LoadAsset(std::filesystem::path path)
{
    const auto ext = path.extension();

    // Check if meta is exist and get meta data
    std::filesystem::path metaPath = std::filesystem::path(path).concat(".meta");
    bool bMetaExisted = std::filesystem::exists(metaPath);
    bool bSkipMemoryCheck = false;

    Meta meta;
    
    if (!bMetaExisted)
    {
        meta.guid = xg::newGuid().str();
        Serializer::GetInstance().Serialize(&meta, metaPath.string());
        bSkipMemoryCheck = true;
    }
    else
    {
        Serializer::GetInstance().Deserialize(&meta, metaPath.string());
    }

    xg::Guid guid = xg::Guid(meta.guid);

    // Load Asset
    // Texture
    if (ext == ".jpg" ||
        ext == ".png")
    {
        if (!bSkipMemoryCheck)
            if (mGuid2TextureMap.find(guid) != mGuid2TextureMap.end())
                return true;

        Texture* tex = mTextureStorage.RequestElement();
        TextureLoader::LoadTexture(tex, path.string());
        mGuid2TextureMap.emplace(meta.guid, tex);
    }
    // Mesh
    else if (ext == "obj")
    {
        if (!bSkipMemoryCheck)
            if (mGuid2MeshMap.find(guid) != mGuid2MeshMap.end())
                return true;

        Mesh* mesh = mMeshStorage.RequestElement();
        MeshLoader::LoadObj(mesh, path.string());
        mGuid2MeshMap.emplace(meta.guid, mesh);
    }
    // Material
    else if (ext == "mat")
    {
        if (!bSkipMemoryCheck)
            if (mGuid2MaterialMap.find(guid) != mGuid2MaterialMap.end())
                return true;

        Material* mat = mMaterialStorage.RequestElement();
        MaterialLoader::LoadMaterial(mat, path.string());
        mGuid2MaterialMap.emplace(meta.guid, mat);
    }
    // ShaderLab
    else if (ext == "shader")
    {
        if (!bSkipMemoryCheck)
            if (mGuid2ShaderLabMap.find(guid) != mGuid2ShaderLabMap.end())
                return true;

        ShaderLab* shaderLab = mShaderLabStorage.RequestElement();
        ShaderLabCompiler::GetInstance().Compile(shaderLab, path.string());
        mGuid2ShaderLabMap.emplace(meta.guid, shaderLab);
    }
    // Scene
    else if (ext == "scene")
    {
        
    }

    return true;
}