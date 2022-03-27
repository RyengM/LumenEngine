#pragma once

#include <vector>
#include <string>

namespace Lumen::Game
{
    // Vector in math is inherited from baseObject whose size the not the same as vector itself
    // So declare pure vector structure here as Float
    struct Float2
    {
        float x = 0, y = 0;
    };

    struct Float3
    {
        float x = 0, y = 0, z = 0;
    };

    struct Float4
    {
        float x = 0, y = 0, z = 0, w = 0;
    };

    struct Vertex
    {
        Float3 pos;
        Float3 normal;
        Float3 tangentU;
        Float2 texCoord;

        Vertex() {}
        Vertex(const Float3& pos) : pos(pos) {}
        Vertex(const Float3& pos, const Float2& texC) : pos(pos), texCoord(texC) {};
    };

    struct Mesh
    {
        std::string name;
        bool bTangent = false;

        std::vector<Vertex> vertices;
        std::vector<std::uint16_t> indices;

        Mesh() {}
        Mesh(const Mesh& mesh);
    };

    class MeshLoader
    {
    public:
        static void LoadObj(Mesh* mesh, std::string_view sourceFile);
    };

    class MeshGenerator
    {
    public:
        // The number of vertex is m * n
        static Mesh CreateGrid(float width, float depth, float m, float n);
    };
}