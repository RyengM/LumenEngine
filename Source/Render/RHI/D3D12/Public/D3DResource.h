#pragma once

#include "D3DDevice.h"
#include "Render/RHI/Common/Public/RHIResource.h"
#include "Render/RHI/Common/Public/RHICommandBuffer.h"

namespace Lumen::Render
{
    class D3DResourceUtility
    {
    public:
        static DXGI_FORMAT GetTextureFormat(EGraphicsFormat format);
        static DXGI_FORMAT GetTextureViewFormat(EGraphicsFormat format);
        static D3D12_RESOURCE_DIMENSION GetResourceDimension(ETextureType type);
        static D3D12_RTV_DIMENSION GetRTVDimension(ETextureType type);
        static D3D12_SRV_DIMENSION GetSRVDimension(ETextureType type);
        static D3D12_RESOURCE_FLAGS GetTextureFlags(EUsageType flag);
    };

    struct D3DBuffer : public RHIBuffer
    {
        D3DBuffer(RHIDevice* rhiDevice, const BufferDescriptor& descriptor);
        // Update buffer field, constant buffer must be multiplies of 256 bytes
        template<typename T>
        void SetData(int index, const T& data, bool bConstant)
        {
            if ((uint32_t)descriptor.storageType & (uint32_t)EStorageType::Static || (uint32_t)descriptor.storageType & (uint32_t)EStorageType::Dynamic)
            {
                int bytesize = bConstant ? ((sizeof(T) + 255) & ~255) : sizeof(T);
                BYTE* uploadData;
                // Map cpu pointer to gpu upload resource so we can copy data to resource
                ThrowIfFailed(uploadResource->Map(0, nullptr, reinterpret_cast<void**>(&uploadData)));
                memcpy(&uploadData[index * bytesize] , &data, sizeof(T));
                uploadResource->Unmap(0, nullptr);
            }
        }
        void UploadData(RHICommandBuffer* rhiCmdBuffer);

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

        UINT                                                vertexByteStride = 0;
        UINT                                                vertexBufferByteSize = 0;
        DXGI_FORMAT                                         indexFormat;
        UINT                                                indexBufferByteSize = 0;
        UINT                                                indexCount = 0;

        D3D12_VERTEX_BUFFER_VIEW VertexBufferView() const
        {
            D3D12_VERTEX_BUFFER_VIEW view;
            view.BufferLocation = vertexBufferGPU->defaultResource->GetGPUVirtualAddress();
            view.StrideInBytes = vertexByteStride;
            view.SizeInBytes = vertexBufferByteSize;
            return view;
        }

        D3D12_INDEX_BUFFER_VIEW IndexBufferView()const
        {
            D3D12_INDEX_BUFFER_VIEW view;
            view.BufferLocation = indexBufferGPU->defaultResource->GetGPUVirtualAddress();
            view.Format = indexFormat;
            view.SizeInBytes = indexBufferByteSize;
            return view;
        }
    };
}