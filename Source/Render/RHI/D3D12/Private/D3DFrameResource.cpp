#include "Render/RHI/D3D12/Public/D3DFrameResource.h"

using namespace Lumen::Render;

D3DFrameResource::D3DFrameResource(RHIDevice* rhiDevice)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);

    ThrowIfFailed(device->d3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(commandAllocator.GetAddressOf())));
}

D3DFrameResource::~D3DFrameResource()
{

}