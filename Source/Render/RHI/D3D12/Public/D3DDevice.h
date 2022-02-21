#pragma once

#include "Render/RHI/Common/Public/RHIDevice.h"
#include "D3DUtil.h"

namespace Lumen::Render
{
    class D3DDevice : public RHIDevice
    {
    public:
        D3DDevice();

    public:
        Microsoft::WRL::ComPtr<ID3D12Device>                d3dDevice;
        Microsoft::WRL::ComPtr<IDXGIFactory4>               dxgiFactory;
    };
}