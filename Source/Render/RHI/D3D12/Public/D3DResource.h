#pragma once

#include "D3DDevice.h"
#include "Render/RHI/Common/Public/RHIResource.h"

namespace Lumen::Render
{
    class D3DResourceUtility
    {
    public:
        static DXGI_FORMAT GetTextureFormat(EGraphicsFormat format);
        static DXGI_FORMAT GetTextureViewFormat(EGraphicsFormat format);
        static D3D12_RESOURCE_DIMENSION GetResourceDimension(ETextureType type);
        static D3D12_RTV_DIMENSION GetRTVDimension(ETextureType type);
    };

    struct D3DBuffer : public RHIBuffer
    {
        D3DBuffer(RHIDevice* rhiDevice, const BufferDescriptor& descriptor);

        Microsoft::WRL::ComPtr<ID3D12Resource>              defaultResource;
        Microsoft::WRL::ComPtr<ID3D12Resource>              uploadResource;
        Microsoft::WRL::ComPtr<ID3D12Resource>              readbackResource;
    };

    struct D3DTexture : public RHITexture
    {
        D3DTexture() = default;
        D3DTexture(RHIDevice* rhiDevice, const TextureDescriptor& descriptor);

        Microsoft::WRL::ComPtr<ID3D12Resource>              defaultResource;
        Microsoft::WRL::ComPtr<ID3D12Resource>              uploadResource;
        Microsoft::WRL::ComPtr<ID3D12Resource>              readbackResource;
    };

    struct D3DMaterial : public RHIMaterial
    {

    };

    struct D3DMeshGeometry : public RHIMeshGeometry
    {
        Microsoft::WRL::ComPtr<ID3DBlob>                    vertexBufferCPU = nullptr;
        Microsoft::WRL::ComPtr<ID3DBlob>                    indexBufferCPU  = nullptr;

        std::unique_ptr<D3DBuffer>                          vertexBufferGPU;
        std::unique_ptr<D3DBuffer>                          indexBufferGPU;
    };
}