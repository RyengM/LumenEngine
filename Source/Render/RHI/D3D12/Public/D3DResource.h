#pragma once

#include "D3DResourceView.h"
#include "MathHelper.h"
#include <DirectXMath.h>

namespace Lumen::Render
{
    struct D3DBuffer : public RHIBuffer
    {
        D3DBuffer() = default;
        D3DBuffer(RHIDevice* rhiDevice, const BufferDescriptor& descriptor);

        std::unique_ptr<D3DBufferResource>                  resource;
    };

    struct D3DPlainTexture : public RHIPlainTexture
    {
        D3DPlainTexture() = default;
        D3DPlainTexture(RHIDevice* rhiDevice, D3DDescriptorHeap* srvDescHeap, const TextureDescriptor& desc);

        //void Set2DData(RHIDevice* device, const void* data);

        std::unique_ptr<D3DTextureResource>                 resource;
        std::unique_ptr<D3DShaderResourceView>              srvView;
    };

    struct D3DRenderTarget : public RHIRenderTarget
    {
        D3DRenderTarget() = default;
        D3DRenderTarget(RHIDevice* rhiDevice, D3DDescriptorHeap* srvDescHeap, D3DDescriptorHeap* rtvDescHeap, const TextureDescriptor& desc);

        std::unique_ptr<D3DTextureResource>                 resource;
        std::unique_ptr<D3DShaderResourceView>              srvView;
        std::unique_ptr<D3DRenderTargetView>                rtvView;
    };

    struct D3DDepthBuffer : public RHIDepthBuffer
    {
        D3DDepthBuffer() = default;
        D3DDepthBuffer(RHIDevice* rhiDevice, D3DDescriptorHeap* srvDescHeap, D3DDescriptorHeap* dsvDescHeap, const TextureDescriptor& desc);

        std::unique_ptr<D3DTextureResource>                 resource;
        std::unique_ptr<D3DDepthStencilView>                dsvView;
    };

    struct D3DDepthRenderTarget : public RHIDepthRenderTarget
    {
        D3DDepthRenderTarget() = default;
        D3DDepthRenderTarget(RHIDevice* rhiDevice, D3DDescriptorHeap* srvDescHeap, D3DDescriptorHeap* rtvDescHeap, D3DDescriptorHeap* dsvDescHeap, const TextureDescriptor& colorDesc, const TextureDescriptor& depthDesc);

        TextureDescriptor                                   depthDescriptor;
        std::unique_ptr<D3DRenderTarget>                    colorBuffer;
        std::unique_ptr<D3DDepthBuffer>                     depthBuffer;
    };

    struct D3DMaterial : public RHIMaterial
    {
        D3DMaterial() = default;
        
        // Index to constant buffer
        int matCBIndex = -1;

        // Index to SRV heap for diffuse texture
        int diffuseSrvHandle = -1;

        // Index to SRV heap for normal texture
        int normalSrvHandle = -1;
        
        DirectX::XMFLOAT4 diffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
        DirectX::XMFLOAT3 fresnelR0 = { 0.01f, 0.01f, 0.01f };
        float roughness = 0.25f;
    };

    struct D3DMeshGeometry : public RHIMeshGeometry
    {
        Microsoft::WRL::ComPtr<ID3DBlob>                    vertexBufferCPU = nullptr;
        Microsoft::WRL::ComPtr<ID3DBlob>                    indexBufferCPU  = nullptr;

        std::unique_ptr<D3DBuffer>                          vertexBufferGPU;
        std::unique_ptr<D3DBuffer>                          indexBufferGPU;

        UINT                                                vertexByteStride = 0;
        UINT                                                vertexBufferByteSize = 0;
        DXGI_FORMAT                                         indexFormat;
        UINT                                                indexBufferByteSize = 0;
        UINT                                                indexCount = 0;

        D3D12_VERTEX_BUFFER_VIEW VertexBufferView() const
        {
            D3D12_VERTEX_BUFFER_VIEW view;
            view.BufferLocation = vertexBufferGPU->resource->defaultResource->GetGPUVirtualAddress();
            view.StrideInBytes = vertexByteStride;
            view.SizeInBytes = vertexBufferByteSize;
            return view;
        }

        D3D12_INDEX_BUFFER_VIEW IndexBufferView()const
        {
            D3D12_INDEX_BUFFER_VIEW view;
            view.BufferLocation = indexBufferGPU->resource->defaultResource->GetGPUVirtualAddress();
            view.Format = indexFormat;
            view.SizeInBytes = indexBufferByteSize;
            return view;
        }
    };

    struct D3DRenderItem : public RHIRenderItem
    {
        DirectX::XMFLOAT4X4 world = MathHelper::Identity4x4();

        UINT objectCBIndex = -1;

        // TODO. build material system
        D3D12_GPU_DESCRIPTOR_HANDLE diffuseHandle;

        D3DMeshGeometry* mesh;
        D3D12_PRIMITIVE_TOPOLOGY primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

        // Same id with entity in the scene
        std::string guid;
    };

    struct D3DLight
    {
        DirectX::XMFLOAT3 strength = { 0.5f, 0.5f, 0.5f };
        float falloffStart = 1.0f;
        DirectX::XMFLOAT3 direction = { 0.0f, -1.0f, 0.0f };
        float falloffEnd = 10.0f;
        DirectX::XMFLOAT3 position = { 0.0f, 0.0f, 0.0f };
        float spotPower = 64.0f;
    };
}