#pragma once

#include "Game/Asset/Public/ShaderLabGenerator.h"

namespace Lumen::Game
{
    class ShaderLabCompiler
    {
    public:
        static ShaderLabCompiler& GetInstance();

        ShaderLab Compile(std::string_view sourceFile);

    private:
        ShaderLabCompiler() = default;
        ~ShaderLabCompiler() = default;

    private:
        ShaderLabGenerator mShaderLabGenerator;
    };
}