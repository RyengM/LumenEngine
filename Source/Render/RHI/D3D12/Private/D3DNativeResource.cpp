#include "Render/RHI/D3D12/Public/D3DNativeResource.h"
#include "Render/RHI/D3D12/Public/D3DCommandBuffer.h"

using namespace Lumen::Render;

DXGI_FORMAT D3DResourceUtility::GetTextureFormat(EGraphicsFormat format)
{
    if (format == EGraphicsFormat::R8_SRGB)
        return DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;
    else if (format == EGraphicsFormat::R8G8_SRGB)
        return DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM;
    else if (format == EGraphicsFormat::R8G8B8A8_SRGB)
        return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    else if (format == EGraphicsFormat::R8_UNorm)
        return DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;
    else if (format == EGraphicsFormat::R8G8_UNorm)
        return DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM;
    else if (format == EGraphicsFormat::R8G8B8A8_UNorm)
        return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
    else if (format == EGraphicsFormat::D24_S8_UNorm)
        return DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;

    return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
}

DXGI_FORMAT D3DResourceUtility::GetTextureViewFormat(EGraphicsFormat format)
{
    if (format == EGraphicsFormat::R8_SRGB)
        return DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;
    else if (format == EGraphicsFormat::R8G8_SRGB)
        return DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM;
    else if (format == EGraphicsFormat::R8G8B8A8_SRGB)
        return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    else if (format == EGraphicsFormat::R8_UNorm)
        return DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;
    else if (format == EGraphicsFormat::R8G8_UNorm)
        return DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM;
    else if (format == EGraphicsFormat::R8G8B8A8_UNorm)
        return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
    else if (format == EGraphicsFormat::D24_S8_UNorm)
        return DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;

    return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
}

D3D12_RESOURCE_DIMENSION D3DResourceUtility::GetResourceDimension(ETextureType type)
{
    if (type == ETextureType::Tex2D || type == ETextureType::Tex2DArray || type == ETextureType::TexCube || type == ETextureType::TexCubeArray)
        return D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    else if (type == ETextureType::Tex3D)
        return D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_TEXTURE3D;

    return D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_UNKNOWN;
}

D3D12_RTV_DIMENSION D3DResourceUtility::GetRTVDimension(ETextureType type)
{
    if (type == ETextureType::Tex2D)
        return D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;
    else if (type == ETextureType::Tex2DArray)
        return D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
    else if (type == ETextureType::Tex3D)
        return D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE3D;

    return D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_UNKNOWN;
}

D3D12_SRV_DIMENSION D3DResourceUtility::GetSRVDimension(ETextureType type)
{
    if (type == ETextureType::Tex2D)
        return D3D12_SRV_DIMENSION::D3D12_SRV_DIMENSION_TEXTURE2D;
    else if (type == ETextureType::Tex2DArray)
        return D3D12_SRV_DIMENSION::D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
    else if (type == ETextureType::Tex3D)
        return D3D12_SRV_DIMENSION::D3D12_SRV_DIMENSION_TEXTURE3D;

    return D3D12_SRV_DIMENSION::D3D12_SRV_DIMENSION_UNKNOWN;
}

D3D12_RESOURCE_FLAGS D3DResourceUtility::GetTextureFlags(EUsageType type)
{
    if (type == EUsageType::DepthStencil)
        return D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
    else if (type == EUsageType::RenderTarget)
        return D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
    else if (type == EUsageType::UnorderedAccess)
        return D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    return D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
}

D3D12_RESOURCE_STATES D3DResourceUtility::GetBufferInitState(EBufferInitState state)
{
    if (state == EBufferInitState::CopyDest)
        return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COPY_DEST;
    else if (state == EBufferInitState::CopySrc)
        return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COPY_SOURCE;
    else if (state == EBufferInitState::VertexAndConstant)
        return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
    else if (state == EBufferInitState::GenericRead)
        return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ;
    return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COMMON;
}

D3D12_RESOURCE_STATES D3DResourceUtility::GetTextureInitState(ETextureInitState state)
{
    if (state == ETextureInitState::DepthRead)
        return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_DEPTH_READ;
    else if (state == ETextureInitState::DepthWrite)
        return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_DEPTH_WRITE;
    else if (state == ETextureInitState::PixelShaderResource)
        return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
    else if (state == ETextureInitState::RenderTarget)
        return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET;
    else if (state == ETextureInitState::Unordered)
        return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
    else if (state == ETextureInitState::GenericRead)
        return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ;
    else if (state == ETextureInitState::CopyDest)
        return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COPY_DEST;
    return D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COMMON;
}

D3DBufferResource::D3DBufferResource(RHIDevice* rhiDevice, const BufferDescriptor& desc)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);
    descriptor = desc;

    // Default memory
    if ((uint32_t)descriptor.storageType & (uint32_t)EStorageType::Default)
    {
        D3D12_HEAP_PROPERTIES defaultHeapProperties;
        {
            defaultHeapProperties.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT;
            defaultHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
            defaultHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
            defaultHeapProperties.VisibleNodeMask = 1;
            defaultHeapProperties.CreationNodeMask = 1;
        }
        D3D12_RESOURCE_DESC defaultResourceDesc;
        {
            defaultResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
            defaultResourceDesc.Alignment = 0;
            defaultResourceDesc.Width = descriptor.stride * descriptor.count;
            defaultResourceDesc.Height = 1;
            defaultResourceDesc.DepthOrArraySize = 1;
            defaultResourceDesc.MipLevels = 1;
            defaultResourceDesc.Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
            defaultResourceDesc.SampleDesc.Count = 1;
            defaultResourceDesc.SampleDesc.Quality = 0;
            defaultResourceDesc.Flags = D3DResourceUtility::GetTextureFlags(descriptor.usageType);
            defaultResourceDesc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        }
        ThrowIfFailed(device->d3dDevice->CreateCommittedResource(&defaultHeapProperties, D3D12_HEAP_FLAG_NONE, &defaultResourceDesc, 
            D3DResourceUtility::GetBufferInitState(descriptor.initState), nullptr, IID_PPV_ARGS(defaultResource.GetAddressOf())));
    }

    // Upload Memory
    if ((uint32_t)descriptor.storageType & ((uint32_t)EStorageType::Static | (uint32_t)EStorageType::Dynamic))
    {
        D3D12_HEAP_PROPERTIES uploadHeapProperties;
        {
            uploadHeapProperties.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;
            uploadHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
            uploadHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
            uploadHeapProperties.VisibleNodeMask = 1;
            uploadHeapProperties.CreationNodeMask = 1;
        }
        D3D12_RESOURCE_DESC uploadResourceDesc;
        {
            uploadResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
            uploadResourceDesc.Alignment = 0;
            uploadResourceDesc.Width = descriptor.stride * descriptor.count;
            uploadResourceDesc.Height = 1;
            uploadResourceDesc.DepthOrArraySize = 1;
            uploadResourceDesc.MipLevels = 1;
            uploadResourceDesc.Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
            uploadResourceDesc.SampleDesc.Count = 1;
            uploadResourceDesc.SampleDesc.Quality = 0;
            uploadResourceDesc.Flags = D3DResourceUtility::GetTextureFlags(descriptor.usageType);
            uploadResourceDesc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        }
        ThrowIfFailed(device->d3dDevice->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
            &uploadResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(uploadResource.GetAddressOf())));
    }

    // Readback Memory
    if ((uint32_t)descriptor.storageType & (uint32_t)EStorageType::Staging)
    {
        D3D12_HEAP_PROPERTIES readbackHeapProperties;
        {
            readbackHeapProperties.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_READBACK;
            readbackHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
            readbackHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
            readbackHeapProperties.VisibleNodeMask = 1;
            readbackHeapProperties.CreationNodeMask = 1;
        }
        D3D12_RESOURCE_DESC readbackResourceDesc;
        {
            readbackResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
            readbackResourceDesc.Alignment = 0;
            readbackResourceDesc.Width = descriptor.stride * descriptor.count;
            readbackResourceDesc.Height = 1;
            readbackResourceDesc.DepthOrArraySize = 1;
            readbackResourceDesc.MipLevels = 1;
            readbackResourceDesc.Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
            readbackResourceDesc.SampleDesc.Count = 1;
            readbackResourceDesc.SampleDesc.Quality = 0;
            readbackResourceDesc.Flags = D3DResourceUtility::GetTextureFlags(descriptor.usageType);
            readbackResourceDesc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        }
        ThrowIfFailed(device->d3dDevice->CreateCommittedResource(&readbackHeapProperties, D3D12_HEAP_FLAG_NONE,
            &readbackResourceDesc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(readbackResource.GetAddressOf())));
    }
}

void D3DBufferResource::UploadData(RHICommandBuffer* cmdBuffer)
{
    if ((uint32_t)descriptor.storageType & (uint32_t)EStorageType::Default &&
        ((uint32_t)descriptor.storageType & (uint32_t)EStorageType::Static || (uint32_t)descriptor.storageType & (uint32_t)EStorageType::Dynamic))
    {
        D3DCommandBuffer* cmdList = static_cast<D3DCommandBuffer*>(cmdBuffer);

        CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(defaultResource.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
        CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_COMMON);

        cmdList->commandList->ResourceBarrier(1, &beforeBarrier);
        cmdList->commandList->CopyBufferRegion(defaultResource.Get(), 0, uploadResource.Get(), 0, descriptor.count * descriptor.stride);
        cmdList->commandList->ResourceBarrier(1, &afterBarrier);
    }
}

D3DTextureResource::D3DTextureResource(RHIDevice* rhiDevice, const TextureDescriptor& desc)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);
    descriptor = desc;

    // Default memory
    if ((uint32_t)descriptor.storageType & (uint32_t)EStorageType::Default)
    {
        D3D12_HEAP_PROPERTIES defaultHeapProperties;
        {
            defaultHeapProperties.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT;
            defaultHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
            defaultHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
            defaultHeapProperties.VisibleNodeMask = 1;
            defaultHeapProperties.CreationNodeMask = 1;
        }
        D3D12_RESOURCE_DESC defaultResourceDesc;
        {
            defaultResourceDesc.Dimension = D3DResourceUtility::GetResourceDimension(descriptor.textureType);
            defaultResourceDesc.Alignment = 0;
            defaultResourceDesc.Width = descriptor.width;
            defaultResourceDesc.Height = descriptor.height;
            defaultResourceDesc.DepthOrArraySize = descriptor.slices;
            defaultResourceDesc.MipLevels = descriptor.mipLevel;
            defaultResourceDesc.Format = D3DResourceUtility::GetTextureFormat(descriptor.format);
            defaultResourceDesc.SampleDesc.Count = (UINT)descriptor.sample;
            defaultResourceDesc.SampleDesc.Quality = 0;
            defaultResourceDesc.Flags = D3DResourceUtility::GetTextureFlags(descriptor.usageType);
            defaultResourceDesc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_UNKNOWN;
        }

        D3D12_CLEAR_VALUE clearValue;
        clearValue.Format = D3DResourceUtility::GetTextureFormat(descriptor.format);
        if (descriptor.usageType == EUsageType::DepthStencil)
        {
            clearValue.DepthStencil.Depth = 1.0f;
            clearValue.DepthStencil.Stencil = 0;
            ThrowIfFailed(device->d3dDevice->CreateCommittedResource(&defaultHeapProperties, D3D12_HEAP_FLAG_NONE, &defaultResourceDesc,
                D3DResourceUtility::GetTextureInitState(descriptor.initState), &clearValue, IID_PPV_ARGS(defaultResource.GetAddressOf())));
        }
        else if (descriptor.usageType == EUsageType::RenderTarget)
        {
            const float color[4] = { 0, 0, 0, 0 };
            clearValue = CD3DX12_CLEAR_VALUE{ D3DResourceUtility::GetTextureFormat(descriptor.format), color };
            ThrowIfFailed(device->d3dDevice->CreateCommittedResource(&defaultHeapProperties, D3D12_HEAP_FLAG_NONE, &defaultResourceDesc,
                D3DResourceUtility::GetTextureInitState(descriptor.initState), &clearValue, IID_PPV_ARGS(defaultResource.GetAddressOf())));
        }
        else
        {
            ThrowIfFailed(device->d3dDevice->CreateCommittedResource(&defaultHeapProperties, D3D12_HEAP_FLAG_NONE, &defaultResourceDesc,
                D3DResourceUtility::GetTextureInitState(descriptor.initState), nullptr, IID_PPV_ARGS(defaultResource.GetAddressOf())));
        }
    }
    // Upload memory
    if ((uint32_t)descriptor.storageType & ((uint32_t)EStorageType::Static | (uint32_t)EStorageType::Dynamic))
    {
        D3D12_HEAP_PROPERTIES uploadHeapProperties;
        {
            uploadHeapProperties.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;
            uploadHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
            uploadHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
            uploadHeapProperties.VisibleNodeMask = 1;
            uploadHeapProperties.CreationNodeMask = 1;
        }
        D3D12_RESOURCE_DESC uploadResourceDesc;
        {
            uploadResourceDesc.Dimension = D3DResourceUtility::GetResourceDimension(descriptor.textureType);
            uploadResourceDesc.Alignment = 0;
            uploadResourceDesc.Width = descriptor.width;
            uploadResourceDesc.Height = descriptor.height;
            uploadResourceDesc.DepthOrArraySize = descriptor.slices;
            uploadResourceDesc.MipLevels = descriptor.mipLevel;
            uploadResourceDesc.Format = D3DResourceUtility::GetTextureFormat(descriptor.format);
            uploadResourceDesc.SampleDesc.Count = (UINT)descriptor.sample;
            uploadResourceDesc.SampleDesc.Quality = 0;
            uploadResourceDesc.Flags = D3DResourceUtility::GetTextureFlags(descriptor.usageType);
            uploadResourceDesc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_UNKNOWN;
        }
        // Texture resource cannot be created on upload buffer or readback heap
        if (descriptor.usageType == EUsageType::Default)
        {
            uploadResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
            uploadResourceDesc.Width = descriptor.width * descriptor.height * 4;
            uploadResourceDesc.Height = 1;
            uploadResourceDesc.Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
            uploadResourceDesc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        }
        ThrowIfFailed(device->d3dDevice->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
            &uploadResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(uploadResource.GetAddressOf())));
    }
    // Readback memory
    if ((uint32_t)descriptor.storageType & (uint32_t)EStorageType::Staging)
    {
        D3D12_HEAP_PROPERTIES readbackHeapProperties;
        {
            readbackHeapProperties.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_READBACK;
            readbackHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
            readbackHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
            readbackHeapProperties.VisibleNodeMask = 1;
            readbackHeapProperties.CreationNodeMask = 1;
        }
        D3D12_RESOURCE_DESC readbackResourceDesc;
        {
            readbackResourceDesc.Dimension = D3DResourceUtility::GetResourceDimension(descriptor.textureType);
            readbackResourceDesc.Alignment = 0;
            readbackResourceDesc.Width = descriptor.width;
            readbackResourceDesc.Height = descriptor.height;
            readbackResourceDesc.DepthOrArraySize = descriptor.slices;
            readbackResourceDesc.MipLevels = descriptor.mipLevel;
            readbackResourceDesc.Format = D3DResourceUtility::GetTextureFormat(descriptor.format);
            readbackResourceDesc.SampleDesc.Count = (UINT)descriptor.sample;
            readbackResourceDesc.SampleDesc.Quality = 0;
            readbackResourceDesc.Flags = D3DResourceUtility::GetTextureFlags(descriptor.usageType);
            readbackResourceDesc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_UNKNOWN;
        }
        ThrowIfFailed(device->d3dDevice->CreateCommittedResource(&readbackHeapProperties, D3D12_HEAP_FLAG_NONE,
            &readbackResourceDesc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(readbackResource.GetAddressOf())));
    }
}