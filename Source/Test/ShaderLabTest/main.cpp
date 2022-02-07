#include "Game/Asset/Public/ShaderLabCompiler.h"

using namespace antlrcpp;
using namespace Lumen::Game;

int main() {
    ShaderLab* shaderLab = new ShaderLab();
    ShaderLabCompiler::GetInstance().Compile(shaderLab, "Test.shader");

    return 0;
}