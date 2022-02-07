#include "Game/Asset/Public/mesh.h"
#include <unordered_map>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace Lumen::Game;

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
    std::vector<Vec3> pos(vertexCount);
    std::vector<Vec3> normal(normalCount);
    std::vector<Vec2> texCoord(texCount);
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