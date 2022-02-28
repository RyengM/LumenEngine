#pragma once

#include "D3DPipelineState.h"
#include "Render/RHI/Common/Public/RHIShader.h"

namespace Lumen::Render
{
    struct D3DShader : public RHIShader
    {
        D3DShader(std::string_view sourceFile);

        Microsoft::WRL::ComPtr<ID3DBlob>                    vertexShader;
        Microsoft::WRL::ComPtr<ID3DBlob>                    pixelShader;
    };
}