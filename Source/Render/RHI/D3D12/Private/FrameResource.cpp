#include "Render/RHI/D3D12/Public/FrameResource.h"

FrameResource::FrameResource(ID3D12Device* device, UINT passCount, UINT objectCount, UINT materialCount)
{
    ThrowIfFailed(device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(cmdListAlloc.GetAddressOf())));

    passCB = std::make_unique<UploadBuffer<PassConstants>>(device, passCount, true);
	materialBuffer = std::make_unique<UploadBuffer<MaterialData>>(device, materialCount, false);
    objectCB = std::make_unique<UploadBuffer<ObjectConstants>>(device, objectCount, true);
}

FrameResource::~FrameResource()
{

}