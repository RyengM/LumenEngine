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
}