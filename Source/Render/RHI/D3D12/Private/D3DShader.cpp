#include "Render/RHI/D3D12/Public/D3DShader.h"

using namespace Lumen::Render;

D3DShader::D3DShader(std::string_view hlsl)
{

    ThrowIfFailed(D3DCompile(hlsl.data(), hlsl.size(), NULL, NULL, NULL, "VS", "vs_5_0", 0, 0, &vertexShader, NULL));
    ThrowIfFailed(D3DCompile(hlsl.data(), hlsl.size(), NULL, NULL, NULL, "PS", "ps_5_0", 0, 0, &pixelShader, NULL));
}