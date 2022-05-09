#include "Render/RHI/D3D12/Public/D3DFrameResource.h"

using namespace Lumen::Render;

D3DFrameResource::D3DFrameResource(RHIDevice* rhiDevice)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);

    ThrowIfFailed(device->d3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(commandAllocator.GetAddressOf())));

    BufferDescriptor desc;
    {
        desc.name = "passCB";
        desc.count = 1;
        desc.stride = CalcStride(sizeof(PassConstants));
        desc.usageType = EUsageType::Default;
        desc.bufferType = EBufferType::Constant;
        desc.storageType = EStorageType::Dynamic;
    };
    passBuffers = std::make_unique<D3DBufferResource>(device, desc);
    {
        desc.name = "objectCB";
        desc.count = 1024;
        desc.stride = CalcStride(sizeof(ObjectConstants));
    }
    objectBuffers = std::make_unique<D3DBufferResource>(device, desc);
    {
        // Note that the size of material CB is not fixed, but aligned with 256
        desc.name = "materialCB";
        desc.count = 128;
        desc.stride = 256;
    }
    materialBuffers = std::make_unique<D3DBufferResource>(device, desc);
}

D3DFrameResource::~D3DFrameResource()
{

}

size_t D3DFrameResource::CalcStride(size_t stride)
{
    return (stride + 255) & ~255;
}