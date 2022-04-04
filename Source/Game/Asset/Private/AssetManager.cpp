#include "Game/Asset/Public/AssetManager.h"
#include "Game/Asset/Public/Serializer.h"

using namespace Lumen::Game;
using namespace std::filesystem;

AssetManager::AssetManager()
{
    mScene = std::make_unique<Scene>();
}

void AssetManager::BuildResourceMap()
{
    const char assetFolder[] = "../../Assets";

    EnterDictRecur(assetFolder);
}

void AssetManager::EnterDictRecur(const std::string& dir) {
    directory_iterator list(dir);
    for (auto& it : list) {
        auto path = it.path().string();
        if (it.status().type() == file_type::directory)
            EnterDictRecur(path);
        else if (it.status().type() == file_type::regular)
            LoadAsset(path);
    }
}

bool AssetManager::LoadAsset(std::filesystem::path path)
{
    const auto ext = path.extension();
    const auto stem = path.stem();

    if (ext == ".meta") return true;

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
    if (ext == ".jpg" || ext == ".png")
    {
        if (!bSkipMemoryCheck)
            if (mGuid2TextureMap.find(guid) != mGuid2TextureMap.end())
                return true;

        Texture* tex = mTextureStorage.RequestElement();
        new(tex)Texture();
        tex->name = stem.string();
        TextureLoader::LoadTexture(tex, path.string());
        mGuid2TextureMap.emplace(meta.guid, tex);
    }
    // Mesh
    else if (ext == ".obj")
    {
        if (!bSkipMemoryCheck)
            if (mGuid2MeshMap.find(guid) != mGuid2MeshMap.end())
                return true;

        Mesh* mesh = mMeshStorage.RequestElement();
        new(mesh)Mesh();
        mesh->name = stem.string();
        MeshLoader::LoadObj(mesh, path.string());
        mGuid2MeshMap.emplace(meta.guid, mesh);
    }
    // Material
    else if (ext == ".mat")
    {
        if (!bSkipMemoryCheck)
            if (mGuid2MaterialMap.find(guid) != mGuid2MaterialMap.end())
                return true;

        Material* mat = mMaterialStorage.RequestElement();
        new(mat)Material();
        mat->name = stem.string();
        MaterialLoader::LoadMaterial(mat, path.string());
        mGuid2MaterialMap.emplace(meta.guid, mat);
    }
    // ShaderLab
    else if (ext == ".shader")
    {
        if (!bSkipMemoryCheck)
            if (mGuid2ShaderLabMap.find(guid) != mGuid2ShaderLabMap.end())
                return true;

        ShaderLab* shaderLab = mShaderLabStorage.RequestElement();
        new(shaderLab)ShaderLab();
        shaderLab->name = stem.string();
        ShaderLabCompiler::GetInstance().Compile(shaderLab, path.string());
        mGuid2ShaderLabMap.emplace(meta.guid, shaderLab);
    }
    // Scene
    else if (ext == ".scene")
    {
        mScene = std::make_unique<Scene>();
        Serializer::GetInstance().Deserialize(mScene.get(), path.string());
        mScene->camera.UpdateProjMatrix();
        mScene->camera.Update();
    }

    return true;
}

Mesh* AssetManager::GetMeshByGUID(xg::Guid guid)
{
    Mesh* mesh = mGuid2MeshMap.at(guid);
    return mesh;
}

Texture* AssetManager::GetTextureByGUID(xg::Guid guid)
{
    Texture* tex = mGuid2TextureMap.at(guid);
    return tex;
}

ShaderLab* AssetManager::GetShaderlabByGUID(xg::Guid guid)
{
    ShaderLab* shaderlab = mGuid2ShaderLabMap.at(guid);
    return shaderlab;
}