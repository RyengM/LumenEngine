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
        Vertex(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty, float tz, float u, float v) :
            pos(px, py, pz), normal(nx, ny, nz), tangentU(tx, ty, tz), texCoord(u, v) {}
    };

    struct Mesh
    {
        std::string name;
        bool bTangent = false;

        std::vector<Vertex> vertices;
        std::vector<std::uint32_t> indices;

        Mesh() {}
        Mesh(const Mesh& rhs);
        Mesh(Mesh&& rhs) noexcept;
    };

    class MeshLoader
    {
    public:
        // Deprecated, use assimp instead
        static void LoadObj(Mesh* mesh, std::string_view sourceFile);

        static void LoadModel(Mesh* mesh, std::string_view path);
    };

    class MeshGenerator
    {
    public:
        // The number of vertex is m * n
        static Mesh CreateGrid(float width, float depth, float m, float n);

        static Mesh CreateSphere(float radius, uint32_t sliceCount, uint32_t stackCount);

        static Mesh CreateCube(float width, float height, float depth);
    };
}