#pragma once

#include "D3DDevice.h"
#include "Render/RHI/Common/Public/RHIShader.h"

namespace Lumen::Render
{
    struct D3DGraphicsShader : public RHIGraphicsShader
    {
        D3DGraphicsShader();

        Microsoft::WRL::ComPtr<ID3DBlob>                    vertexShader;
        Microsoft::WRL::ComPtr<ID3DBlob>                    pixelShader;
    };
}