#pragma once

#include "Core/Math/Public/MathUtil.h"
#include <vector>
#include <string>

using namespace Lumen::Core;

namespace Lumen::Game
{
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
        std::vector<std::uint32_t> indices;

        Mesh() {}
        Mesh(const Mesh& rhs);
        Mesh(Mesh&& rhs);
        ~Mesh() {}
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