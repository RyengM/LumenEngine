#include "Render/RHI/D3D12/Public/D3DResourceView.h"

using namespace Lumen::Render;

D3DRenderTargetView::D3DRenderTargetView(RHIDevice* rhiDevice, D3DDescriptorHeap* descriptorHeap, D3DTexture* texture)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);

    ownedDescriptorHeap = descriptorHeap;
    offset = descriptorHeap->RequestElement();
    descriptorHandle = descriptorHeap->cpuHeapStartHandle;
    descriptorHandle.ptr += offset * descriptorHeap->descriptorSize;
    gpuAddress = descriptorHeap->gpuHeapStartHandle.ptr + offset * descriptorHeap->descriptorSize;

    D3D12_RENDER_TARGET_VIEW_DESC rtvDescriptor;
    rtvDescriptor.Format = D3DResourceUtility::GetTextureViewFormat(texture->descriptor.format);
    rtvDescriptor.ViewDimension = D3DResourceUtility::GetRTVDimension(texture->descriptor.textureType);
    // We only use 2d basic texture now
    rtvDescriptor.Texture2D.MipSlice = 0;
    rtvDescriptor.Texture2D.PlaneSlice = 0;

    device->d3dDevice->CreateRenderTargetView(texture->defaultResource.Get(), &rtvDescriptor, descriptorHandle);
}

D3DDepthStencilView::D3DDepthStencilView(RHIDevice* rhiDevice, D3DDescriptorHeap* descriptorHeap, D3DTexture* texture)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);

    ownedDescriptorHeap = descriptorHeap;
    offset = descriptorHeap->RequestElement();
    descriptorHandle = descriptorHeap->cpuHeapStartHandle;
    descriptorHandle.ptr += offset * descriptorHeap->descriptorSize;
    gpuAddress = descriptorHeap->gpuHeapStartHandle.ptr + offset * descriptorHeap->descriptorSize;

    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDescriptor;
    dsvDescriptor.Flags = D3D12_DSV_FLAG_NONE;
    dsvDescriptor.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    dsvDescriptor.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvDescriptor.Texture2D.MipSlice = 0;

    device->d3dDevice->CreateDepthStencilView(texture->defaultResource.Get(), &dsvDescriptor, descriptorHandle);
}

D3DShaderResourceView::D3DShaderResourceView(RHIDevice* rhiDevice, D3DDescriptorHeap* descriptorHeap, D3DTexture* texture)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);

    ownedDescriptorHeap = descriptorHeap;
    offset = descriptorHeap->RequestElement();
    cpuDescriptorHandle = descriptorHeap->cpuHeapStartHandle;
    cpuDescriptorHandle.ptr += offset * descriptorHeap->descriptorSize;
    gpuAddress = descriptorHeap->gpuHeapStartHandle.ptr + offset * descriptorHeap->descriptorSize;

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDescriptor;
    srvDescriptor.Format = D3DResourceUtility::GetTextureViewFormat(texture->descriptor.format);
    srvDescriptor.ViewDimension = D3DResourceUtility::GetSRVDimension(texture->descriptor.textureType);
    // We only use 2d basic texture now
    srvDescriptor.Texture2D.PlaneSlice = 0;
    srvDescriptor.Texture2D.MostDetailedMip = 0;
    srvDescriptor.Texture2D.MipLevels = 1;
    srvDescriptor.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

    device->d3dDevice->CreateShaderResourceView(texture->defaultResource.Get(), &srvDescriptor, cpuDescriptorHandle);
}