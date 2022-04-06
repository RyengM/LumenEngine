#pragma once

#include "D3DDescriptorHeap.h"
#include "Render/RHI/Common/Public/RHIResource.h"
#include "Render/RHI/Common/Public/RHICommandBuffer.h"

namespace Lumen::Render
{
    class D3DResourceUtility
    {
    public:
        static DXGI_FORMAT GetTextureFormat(EGraphicsFormat format);
        static DXGI_FORMAT GetTextureViewFormat(EGraphicsFormat format);
        static int GetTextureChannelNum(EGraphicsFormat format);
        static D3D12_RESOURCE_DIMENSION GetResourceDimension(ETextureType type);
        static D3D12_RTV_DIMENSION GetRTVDimension(ETextureType type);
        static D3D12_SRV_DIMENSION GetSRVDimension(ETextureType type);
        static D3D12_RESOURCE_FLAGS GetTextureFlags(EUsageType flag);
        static D3D12_RESOURCE_STATES GetBufferInitState(EBufferInitState state);
        static D3D12_RESOURCE_STATES GetTextureInitState(ETextureInitState state);
    };

    struct D3DBufferResource
    {
        D3DBufferResource(RHIDevice* rhiDevice, const BufferDescriptor& descriptor);
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
                memcpy(&uploadData[index * bytesize], &data, sizeof(T));
                uploadResource->Unmap(0, nullptr);
            }
        }
        void UploadData(RHICommandBuffer* rhiCmdBuffer);

        BufferDescriptor                                    descriptor;
        Microsoft::WRL::ComPtr<ID3D12Resource>              defaultResource;
        Microsoft::WRL::ComPtr<ID3D12Resource>              uploadResource;
        Microsoft::WRL::ComPtr<ID3D12Resource>              readbackResource;
    };

    struct D3DTextureResource
    {
        D3DTextureResource() = default;
        D3DTextureResource(RHIDevice* rhiDevice, const TextureDescriptor& descriptor);

        TextureDescriptor                                   descriptor;
        Microsoft::WRL::ComPtr<ID3D12Resource>              defaultResource;
        Microsoft::WRL::ComPtr<ID3D12Resource>              uploadResource;
        Microsoft::WRL::ComPtr<ID3D12Resource>              readbackResource;
    };
}