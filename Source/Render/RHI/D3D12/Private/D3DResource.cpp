#include "Render/RHI/D3D12/Public/D3DResourceView.h"
#include "Render/RHI/D3D12/Public/D3DCommandBuffer.h"

using namespace Lumen::Render;

D3DBuffer::D3DBuffer(RHIDevice* rhiDevice, const BufferDescriptor& desc)
{
    descriptor = desc;

    resource = std::make_unique<D3DBufferResource>(rhiDevice, desc);
}

D3DPlainTexture::D3DPlainTexture(RHIDevice* rhiDevice, D3DDescriptorHeap* srvDescHeap, const TextureDescriptor& desc)
{
    descriptor = desc;

    resource = std::make_unique<D3DTextureResource>(rhiDevice, desc);
    srvView = std::make_unique<D3DShaderResourceView>(rhiDevice, srvDescHeap, resource.get());
}

D3DRenderTarget::D3DRenderTarget(RHIDevice* rhiDevice, D3DDescriptorHeap* srvDescHeap, D3DDescriptorHeap* rtvDescHeap, const TextureDescriptor& desc)
{
    descriptor = desc;

    resource = std::make_unique<D3DTextureResource>(rhiDevice, desc);
    srvView = std::make_unique<D3DShaderResourceView>(rhiDevice, srvDescHeap, resource.get());
    rtvView = std::make_unique<D3DRenderTargetView>(rhiDevice, rtvDescHeap, resource.get());
}

D3DDepthBuffer::D3DDepthBuffer(RHIDevice* rhiDevice, D3DDescriptorHeap* srvDescHeap, D3DDescriptorHeap* dsvDescHeap, const TextureDescriptor& desc)
{
    descriptor = desc;

    resource = std::make_unique<D3DTextureResource>(rhiDevice, desc);
    dsvView = std::make_unique<D3DDepthStencilView>(rhiDevice, dsvDescHeap, resource.get());
}

D3DDepthRenderTarget::D3DDepthRenderTarget(RHIDevice* rhiDevice, D3DDescriptorHeap* srvDescHeap, D3DDescriptorHeap* rtvDescHeap, D3DDescriptorHeap* dsvDescHeap, const TextureDescriptor& colorDesc, const TextureDescriptor& depthDesc)
{
    descriptor = colorDesc;
    depthDescriptor = depthDesc;

    colorBuffer = std::make_unique<D3DRenderTarget>(rhiDevice, srvDescHeap, rtvDescHeap, colorDesc);
    depthBuffer = std::make_unique<D3DDepthBuffer>(rhiDevice, srvDescHeap, dsvDescHeap, depthDesc);
}