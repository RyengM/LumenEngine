#pragma once

#include "Render/RHI/D3D12/Public/D3DCommandContext.h"
#include "Render/RHI/D3D12/Public/D3DFence.h"

using namespace Lumen::Render;

D3DFence::D3DFence(RHIDevice* rhiDevice, std::string_view inName)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);

    ThrowIfFailed(device->d3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&d3dFence)));

    name = inName.data() + std::string("_Fence");
    d3dFence->SetName(LPCWSTR(name.c_str()));
}

void D3DFence::Signal(RHICommandContext* rhiContext)
{
    D3DCommandContext* context = static_cast<D3DCommandContext*>(rhiContext);
    context->commandQueue->Signal(d3dFence.Get(), currentFenceValue);
}