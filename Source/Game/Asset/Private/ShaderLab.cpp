#include "Game/Asset/Public/ShaderLab.h"

using namespace Lumen::Game;

ShaderLab::ShaderLab(const ShaderLab& shader)
{
    name = shader.name;
    properties = shader.properties;
    category = shader.category;
}