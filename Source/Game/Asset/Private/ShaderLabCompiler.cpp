#include "Game/Asset/Public/ShaderLabCompiler.h"
#include <fstream>
#include <filesystem>

using namespace Lumen::Game;

ShaderLabCompiler& ShaderLabCompiler::GetInstance()
{
    static ShaderLabCompiler instance;
    return instance;
}

void ShaderLabCompiler::Compile(ShaderLab* shaderLab, std::string_view sourceFile)
{
    std::ifstream ifile(sourceFile.data());
    if (!ifile.is_open())
        return;
    std::ostringstream buf;
    buf << ifile.rdbuf();

    ShaderLab shaderTmp = mShaderLabGenerator.Compile(buf.str());
    shaderLab->name = std::move(shaderTmp.name);
    shaderLab->properties = std::move(shaderTmp.properties);
    shaderLab->category = std::move(shaderTmp.category);

    // Calc property size and layout offsets
    // String will not be filled in material CB layout, it point to the texture bind
    uint32_t offset = 0;
    for (auto& prop : shaderLab->properties)
    {
        if (prop.value.index() == 0) // int
        {
            offset = offset % sizeof(int) ? (offset / sizeof(int) + 1) * sizeof(int) : offset;
            shaderLab->offsets.emplace_back(offset);
            offset += sizeof(int);
        }
        else if (prop.value.index() == 1) // float
        {
            offset = offset % sizeof(float) ? (offset / sizeof(float) + 1) * sizeof(float) : offset;
            shaderLab->offsets.emplace_back(offset);
            offset += sizeof(float);
        }
        else if (prop.value.index() == 2) // Vec4
        {
            int stride = sizeof(float) * 4;
            offset = offset % stride ? (offset / stride + 1) * stride : offset;
            shaderLab->offsets.emplace_back(offset);
            offset += stride;
        }
    }
    // Constant buffer need to be aligned with 256
    shaderLab->propertyCapacity = (offset + 255) & ~255;
}