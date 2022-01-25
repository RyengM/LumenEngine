#include "Game/Asset/Public/ShaderLabCompiler.h"

using namespace antlrcpp;
using namespace Lumen::Game;

int main() {
    ShaderLab shaderLab = ShaderLabCompiler::GetInstance().Compile("Test.hlsl");

    return 0;
}