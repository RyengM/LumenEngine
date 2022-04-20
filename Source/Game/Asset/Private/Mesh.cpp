#include "Game/Asset/Public/mesh.h"
#include "Assimp/Importer.hpp"
#include "Assimp/scene.h"
#include "Assimp/postprocess.h"
#include <unordered_map>
#include <cassert>
#include <fstream>
#include <sstream>

using namespace Lumen::Game;

Mesh AssimpProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    Mesh data;
    data.name = mesh->mName.data;
    Vertex v;
    for (int i = 0; i < mesh->mNumVertices; ++i)
    {
        v.pos.x = mesh->mVertices[i].x;
        v.pos.y = mesh->mVertices[i].y;
        v.pos.z = mesh->mVertices[i].z;

        v.normal.x = mesh->mNormals[i].x;
        v.normal.y = mesh->mNormals[i].y;
        v.normal.z = mesh->mNormals[i].z;

        if (mesh->mTangents)
        {
            v.tangentU.x = mesh->mTangents[i].x;
            v.tangentU.y = mesh->mTangents[i].y;
            v.tangentU.z = mesh->mTangents[i].z;
        }

        if (mesh->mTextureCoords[0])
        {
            v.texCoord.x = mesh->mTextureCoords[0][i].x;
            v.texCoord.y = mesh->mTextureCoords[0][i].y;
        }
        else
            v.texCoord = Float2(0.f);

        data.vertices.push_back(v);
    }

    for (auto i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (auto j = 0; j < mesh->mFaces->mNumIndices; j++)
            data.indices.push_back(face.mIndices[j]);
    }

    return data;
}

void AssimpProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& modelData)
{
    for (int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        modelData.push_back(std::move(AssimpProcessMesh(mesh, scene)));
    }

    for (int i = 0; i < node->mNumChildren; i++)
    {
        AssimpProcessNode(node->mChildren[i], scene, modelData);
    }
}

Mesh::Mesh(const Mesh& rhs)
{
    name = rhs.name;
    bTangent = rhs.bTangent;
    vertices = rhs.vertices;
    indices = rhs.indices;
}

Mesh::Mesh(Mesh&& rhs) noexcept
{
    name = std::move(rhs.name);
    bTangent = rhs.bTangent;
    vertices = std::move(rhs.vertices);
    indices = std::move(rhs.indices);
}

void MeshLoader::LoadModel(Mesh* mesh, std::string_view path)
{
    std::vector<Mesh> modelData;

    Assimp::Importer meshImporter;
    const aiScene* scene = meshImporter.ReadFile(path.data(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LOG_ERROR(meshImporter.GetErrorString());
        return;
    }

    AssimpProcessNode(scene->mRootNode, scene, modelData);

    // Combine mesh data and copy to mesh storage
    int vertexSize = 0, indexSize = 0;
    for (int i = 0; i < modelData.size(); i++)
    {
        vertexSize += modelData[i].vertices.size();
        indexSize += modelData[i].indices.size();
    }
    mesh->vertices.resize(vertexSize);
    mesh->indices.resize(indexSize);
    int offset = 0;
    for (int i = 0; i < modelData.size(); i++)
    {
        memcpy(&mesh->vertices[offset], &modelData[i].vertices[0], modelData[i].vertices.size() * sizeof(Vertex));
        memcpy(&mesh->indices[offset], &modelData[i].indices[0], modelData[i].indices.size() * sizeof(uint32_t));
        offset += modelData[i].vertices.size();
    }
}

void MeshLoader::LoadObj(Mesh* mesh, std::string_view sourceFile)
{
    int vertexCount = 0, normalCount = 0, texCount = 0, faceCount = 0, actualVertexCount = 0;

    // Count and init data
    std::ifstream in;
    in.open(sourceFile.data());
    assert(in.is_open());
    std::string content;
    while (std::getline(in, content))
    {
        if (content[0] == 'v')
        {
            if (content[1] == 'n')
                normalCount++;
            else if (content[1] == 't')
                texCount++;
            else
                vertexCount++;
        }
        else if (content[0] == 'f')
        {
            std::istringstream s(content);
            s >> content;
            for (int i = 0; i < 4; ++i)
            {
                content.clear();
                s >> content;
                if (!content.empty())
                {
                    actualVertexCount++;
                    if (i == 3) faceCount++;
                }
            }
            faceCount++;
        }
    }
    std::vector<Float3> pos(vertexCount);
    std::vector<Float3> normal(normalCount);
    std::vector<Float2> texCoord(texCount);
    mesh->vertices.resize(actualVertexCount);
    mesh->indices.resize(faceCount * 3);
    in.close();
    // Read data
    in.open(sourceFile.data());
    assert(in.is_open());
    // Count number for vertex, normal and texCoord counting
    int v = 0, n = 0, t = 0;
    // Index of vertex and index
    int ivertex = 0, iindex = 0;
    while (std::getline(in, content))
    {
        if (content[0] == 'v')
        {
            if (content[1] == 'n')
            {
                std::istringstream s(content);
                s >> content >> normal[n].x >> normal[n].y >> normal[n].z;
                n++;
            }
            else if (content[1] == 't')
            {
                std::istringstream s(content);
                s >> content >> texCoord[t].x >> texCoord[t].y;
                t++;
            }
            else
            {
                std::istringstream s(content);
                s >> content >> pos[v].x >> pos[v].y >> pos[v].z;
                v++;
            }
        }
        if (content[0] == 'f')
        {
            std::istringstream s(content);
            s >> content;
            for (int i = 0; i < 4; ++i)
            {
                content.clear();
                s >> content;
                // Separate quad into two triangle
                if (i == 3)
                {
                    if (content.empty()) break;
                    mesh->indices[iindex] = mesh->indices[iindex - 3];
                    mesh->indices[iindex + 1] = mesh->indices[iindex - 1];
                    iindex += 2;
                }
                // Count number of '/'
                int countSlash = 0;
                for (int k = 0; k < content.size(); ++k)
                    if (content[k] == '/') countSlash++;
                // Vertex
                int index = 0, j = 0;
                for (j = 0; content[j] != '/'; ++j)
                    index = index * 10 + (content[j] - 48);
                mesh->indices[iindex] = ivertex;
                mesh->vertices[ivertex].pos = pos[index - 1];

                if (countSlash == 1)
                {
                    // TexCoord
                    index = 0;
                    for (j = j + 1; content[j]; ++j)
                        index = index * 10 + (content[j] - 48);
                    mesh->vertices[ivertex].texCoord = texCoord[index - 1];
                }
                else if (countSlash == 2)
                {
                    // TexCoord
                    index = 0;
                    for (j = j + 1; content[j] != '/'; ++j)
                        index = index * 10 + (content[j] - 48);
                    if (index > 0)
                        mesh->vertices[ivertex].texCoord = texCoord[index - 1];
                    // Normal
                    index = 0;
                    for (j = j + 1; content[j]; ++j)
                        index = index * 10 + (content[j] - 48);
                    mesh->vertices[ivertex].normal = normal[index - 1];
                }
                iindex++;
                ivertex++;
            }
        }
    }
    in.close();
}

Mesh MeshGenerator::CreateGrid(float width, float depth, float m, float n)
{
    Mesh mesh;
    mesh.bTangent = true;
    mesh.vertices.resize(m * n);
    mesh.indices.resize((m - 1) * (n - 1) * 6);

    float halfWidth = width / 2.f;
    float halfDepth = depth / 2.f;

    float dx = width / (m - 1);
    float dz = width / (n - 1);

    // Vertex
    for (int i = 0; i < n; ++i)
    {
        float z = halfDepth - i * dz;
        for (int j = 0; j < m; ++j)
        {
            float x = -halfWidth + j * dx;

            mesh.vertices[i * m + j].pos = Float3(x, 0.f, z);
            mesh.vertices[i * m + j].normal = Float3(0.f, 1.f, 0.f);
            mesh.vertices[i * m + j].tangentU = Float3(1.f, 0.f, 0.f);

            // Stretch texture over grid.
            mesh.vertices[i * m + j].texCoord = Float2(j, i);
        }
    }

    // Index
    int k = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < m - 1; ++j)
        {
            mesh.indices[k] = i * m + j;
            mesh.indices[k + 1] = i * m + j + 1;
            mesh.indices[k + 2] = (i + 1) * m + j;

            mesh.indices[k + 3] = (i + 1) * m + j;
            mesh.indices[k + 4] = i * m + j + 1;
            mesh.indices[k + 5] = (i + 1) * m + j + 1;

            k += 6;
        }
    }

    return mesh;
}

Mesh MeshGenerator::CreateSphere(float radius, uint32_t sliceCount, uint32_t stackCount)
{
    Mesh mesh;

    // Compute the vertices stating at the top pole and moving down the stacks.
    // Poles: note that there will be texture coordinate distortion as there is
    // not a unique point on the texture map to assign to the pole when mapping
    // a rectangular texture onto a sphere.
    Vertex topVertex;
    topVertex.pos = Float3(0.f, radius, 0.f);
    topVertex.normal = Float3(0.f, 1.f, 0.f);
    topVertex.tangentU = Float3(1.f, 0.f, 0.f);
    topVertex.texCoord = Float2(0.f, 0.f);
    Vertex bottomVertex = topVertex;
    bottomVertex.pos.y = -radius;
    bottomVertex.normal.y = -1.f;
    bottomVertex.texCoord.y = 1.f;

    mesh.vertices.push_back(topVertex);
    float phiStep = PI / stackCount;
    float thetaStep = 2.0f * PI / sliceCount;

    // Compute vertices for each stack ring (do not count the poles as rings).
    for (uint32_t i = 1; i <= stackCount - 1; ++i)
    {
        float phi = i * phiStep;

        // Vertices of ring.
        for (uint32_t j = 0; j <= sliceCount; ++j)
        {
            float theta = j * thetaStep;

            Vertex v;

            // spherical to cartesian
            v.pos.x = radius * sinf(phi) * cosf(theta);
            v.pos.y = radius * cosf(phi);
            v.pos.z = radius * sinf(phi) * sinf(theta);

            // Partial derivative of P with respect to theta
            v.tangentU.x = -radius * sinf(phi) * sinf(theta);
            v.tangentU.y = 0.0f;
            v.tangentU.z = +radius * sinf(phi) * cosf(theta);
            v.tangentU = MathUtil::Normalize(v.tangentU);

            v.normal = MathUtil::Normalize(v.pos);

            v.texCoord.x = theta / (2.f * PI);
            v.texCoord.y = phi / PI;

            mesh.vertices.push_back(v);
        }
    }

    mesh.vertices.push_back(bottomVertex);

    // Compute indices for top stack.  The top stack was written first to the vertex buffer
    // and connects the top pole to the first ring.
    for (uint32_t i = 1; i <= sliceCount; ++i)
    {
        mesh.indices.push_back(0);
        mesh.indices.push_back(i + 1);
        mesh.indices.push_back(i);
    }

    // Compute indices for inner stacks (not connected to poles).
    // Offset the indices to the index of the first vertex in the first ring.
    // This is just skipping the top pole vertex.
    uint32_t baseIndex = 1;
    uint32_t ringVertexCount = sliceCount + 1;
    for (uint32_t i = 0; i < stackCount - 2; ++i)
    {
        for (uint32_t j = 0; j < sliceCount; ++j)
        {
            mesh.indices.push_back(baseIndex + i * ringVertexCount + j);
            mesh.indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            mesh.indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

            mesh.indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            mesh.indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            mesh.indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
        }
    }

    // Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
    // and connects the bottom pole to the bottom ring.
    // South pole vertex was added last.
    uint32_t southPoleIndex = (uint32_t)mesh.vertices.size() - 1;
    // Offset the indices to the index of the first vertex in the last ring.
    baseIndex = southPoleIndex - ringVertexCount;

    for (uint32_t i = 0; i < sliceCount; ++i)
    {
        mesh.indices.push_back(southPoleIndex);
        mesh.indices.push_back(baseIndex + i);
        mesh.indices.push_back(baseIndex + i + 1);
    }

    return mesh;
}