#include "Game/Asset/Public/mesh.h"
#include <unordered_map>
#include <cassert>
#include <fstream>
#include <sstream>

using namespace Lumen::Game;

Mesh::Mesh(const Mesh& rhs)
{
    name = rhs.name;
    bTangent = rhs.bTangent;
    vertices = rhs.vertices;
    indices = rhs.indices;
}

Mesh::Mesh(Mesh&& rhs)
{
    name = std::move(rhs.name);
    bTangent = rhs.bTangent;
    vertices = std::move(rhs.vertices);
    indices = std::move(rhs.indices);
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