#include "Render/RHI/D3D12/Public/D3DResourceView.h"

using namespace Lumen::Render;

D3DRenderTargetView::D3DRenderTargetView(RHIDevice* rhiDevice, D3DDescriptorHeap* descriptorHeap, D3DTexture* texture)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);

    ownedDescriptorHeap = descriptorHeap;
    INT offset = descriptorHeap->RequestElement();
    descriptorHandle = descriptorHeap->cpuHeapStartHandle;
    descriptorHandle.ptr += offset * descriptorHeap->descriptorSize;

    D3D12_RENDER_TARGET_VIEW_DESC rtvDescriptor;
    rtvDescriptor.Format = D3DResourceUtility::GetTextureViewFormat(texture->descriptor.format);
    rtvDescriptor.ViewDimension = D3DResourceUtility::GetRTVDimension(texture->descriptor.textureType);

    device->d3dDevice->CreateRenderTargetView(texture->defaultResource.Get(), nullptr, descriptorHandle);
}