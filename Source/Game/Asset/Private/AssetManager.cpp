#include "Game/Asset/Public/ShaderLabCompiler.h"
#include "Game/Asset/Public/AssetManager.h"
#include "Game/Asset/Public/Serializer.h"

using namespace Lumen::Game;
using namespace std::filesystem;

std::string GetFileType(file_type type)
{
    if (type == file_type::directory)
        return "Directory";
    else if (type == file_type::regular)
        return "Regular";
    else return "None";
}

AssetManager& AssetManager::GetInstance()
{
    static AssetManager instance;
    return instance;
}

AssetManager::AssetManager()
{
    mScene = std::make_unique<Scene>();

    CreateBuiltInMeshes();
}

void AssetManager::BuildResourceMap()
{
    const char assetFolder[] = "../../Assets";

    auto entry = directory_entry(assetFolder);
    mAssetTree = std::make_unique<AssetTreeNode>(0,
        entry.path().filename().string(), entry.path().string(), GetFileType(entry.status().type()));
    EnterDictRecur(assetFolder, mAssetTree.get());
    // Make sure default shaderlab is existed in asset folder
    bool bHasDefaultShader = false;
    for (auto iter : mGuid2ShaderLabMap)
        if (iter.second->name == "Default")
            bHasDefaultShader = true;
    assert(bHasDefaultShader);
}

void AssetManager::SaveScene()
{
    Serializer::GetInstance().Serialize(mScene.get(), "../../Assets/Scene/simpleScene.scene");
}

void AssetManager::EnterDictRecur(const std::string& dir, AssetTreeNode* node) {
    directory_iterator list(dir);
    for (auto& it : list) {
        auto path = it.path().string();
        auto childNode = std::make_shared<AssetTreeNode>(node->depth + 1,
            it.path().filename().string(), path, GetFileType(it.status().type()));

        if (it.status().type() == file_type::directory)
            EnterDictRecur(path, childNode.get());
        else if (it.status().type() == file_type::regular)
        {
            if (it.path().extension() == ".meta")
                continue;
            // Load asset and build resource map
            LoadAsset(path);
        }

        // Build and fill guid for resource bind
        Meta meta;
        std::filesystem::path metaPath = std::filesystem::path(path).concat(".meta");
        bool bMetaExisted = std::filesystem::exists(metaPath);
        if (!bMetaExisted)
        {
            meta.guid = xg::newGuid().str();
            Serializer::GetInstance().Serialize(&meta, metaPath.string());
        }
        else
            Serializer::GetInstance().Deserialize(&meta, metaPath.string());
        childNode->fileGuid = meta.guid;

        // Build asset tree
        node->children.emplace_back(childNode);
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
        MeshLoader::LoadModel(mesh, path.string());
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
        Serializer::GetInstance().Deserialize(mat, path.string());
        mat->name = stem.string();
        mat->guid = meta.guid;
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
        if (shaderLab->name == "Default") mDefaultShaderGuid = xg::Guid(meta.guid);
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

void AssetManager::CreateMaterial()
{
    Material* mat = mMaterialStorage.RequestElement();
    new(mat)Material();
    mat->name = "new-material_" + std::to_string(matIndex++) + ".mat";
    // Extract shaderlab property to material
    ShaderLab* shader = mGuid2ShaderLabMap.at(mDefaultShaderGuid);
    mat->shaderlab.name = shader->name;
    mat->shaderlab.guid = mDefaultShaderGuid;
    mat->propertyListSize = shader->propertyCapacity;
    for (const auto& prop : shader->properties)
    {
        auto index = prop.value.index();
        if (index == 0)      // int
            mat->propertyList.integerMap.emplace(prop.name, std::get<int>(prop.value));
        else if (index == 1) // float
            mat->propertyList.floatMap.emplace(prop.name, std::get<float>(prop.value));
        else if (index == 2) // vec4
            mat->propertyList.colorMap.emplace(prop.name, std::get<Vec4>(prop.value));
        else if (index == 3) // string
            mat->propertyList.texMap.emplace(prop.name, AssetRef(prop.displayName, std::get<std::string>(prop.value)));
    }
    mat->InitBuffer(shader);
    mat->UpdateBuffer();
    // Save default material and related .meta file
    std::filesystem::path path = "../../Assets/Material/" + mat->name;
    Serializer::GetInstance().Serialize(mat, path.string());
    Meta meta;
    std::filesystem::path metaPath = std::filesystem::path(path).concat(".meta");
    meta.guid = xg::newGuid().str();
    mat->guid = meta.guid;
    Serializer::GetInstance().Serialize(&meta, metaPath.string());
    // Add material info to asset tree
    for (auto node : mAssetTree->children)
        if (node->fileName == "Material")
        {
            auto childNode = std::make_shared<AssetTreeNode>(node->depth + 1, path.filename().string(), path.string(), "Regular");
            childNode->fileGuid = meta.guid;
            node->children.emplace_back(childNode);
        }
    // Add material to map
    mGuid2MaterialMap.emplace(meta.guid, mat);
}

void AssetManager::CreateBuiltInMeshes()
{
    Mesh* mesh = mMeshStorage.RequestElement();
    new(mesh)Mesh(MeshGenerator::CreateSphere(0.5f, 20, 20));
    mesh->name = "sphere-builtin";
    mBuiltInMeshMap[mesh->name] = mesh;
}

Mesh* AssetManager::GetMeshByGUID(xg::Guid guid)
{
    Mesh* mesh = nullptr;
    if (mGuid2MeshMap.find(guid) != mGuid2MeshMap.end())
        mesh = mGuid2MeshMap.at(guid);
    return mesh;
}

Texture* AssetManager::GetTextureByGUID(xg::Guid guid)
{
    Texture* tex = nullptr;
    if (mGuid2TextureMap.find(guid) != mGuid2TextureMap.end())
        tex = mGuid2TextureMap.at(guid);
    return tex;
}

Material* AssetManager::GetMaterialByGUID(xg::Guid guid)
{
    Material* mat = nullptr;
    if (mGuid2MaterialMap.find(guid) != mGuid2MaterialMap.end())
        mat = mGuid2MaterialMap.at(guid);
    return mat;
}

ShaderLab* AssetManager::GetShaderlabByGUID(xg::Guid guid)
{
    ShaderLab* shaderlab = nullptr;
    if (mGuid2ShaderLabMap.find(guid) != mGuid2ShaderLabMap.end())
        shaderlab = mGuid2ShaderLabMap.at(guid);
    return shaderlab;
}