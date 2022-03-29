#include "Game/Asset/Public/ShaderLab.h"

using namespace Lumen::Game;

ShaderLab::ShaderLab(const ShaderLab& rhs)
{
    name = rhs.name;
    properties = rhs.properties;
    category = rhs.category;
}

ShaderLab::ShaderLab(ShaderLab&& rhs)
{
    name = std::move(rhs.name);
    properties = std::move(rhs.properties);
    category = std::move(rhs.category);
}