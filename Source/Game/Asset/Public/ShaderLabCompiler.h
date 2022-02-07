#pragma once

#include "Game/Asset/Public/ShaderLabGenerator.h"

namespace Lumen::Game
{
    class ShaderLabCompiler
    {
    public:
        static ShaderLabCompiler& GetInstance();

        void Compile(ShaderLab* shaderLab, std::string_view sourceFile);

    private:
        ShaderLabCompiler() = default;
        ~ShaderLabCompiler() = default;

    private:
        ShaderLabGenerator mShaderLabGenerator;
    };
}