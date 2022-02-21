#pragma once

#include "D3DResource.h"
#include "MathHelper.h"

namespace Lumen::Render
{
    struct ObjectConstants
    {
        DirectX::XMFLOAT4X4 model = MathHelper::Identity4x4();
    };

    struct PassConstants
    {
        DirectX::XMFLOAT4X4 view = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 proj = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 viewProj = MathHelper::Identity4x4();
        DirectX::XMFLOAT3 eyePos = { 0.0f, 0.0f, 0.0f };
    };

    // Stores the resources needed for the CPU to build the command lists for a frame.  
    struct D3DFrameResource
    {
    public:

        D3DFrameResource(RHIDevice* rhiDevice);
        D3DFrameResource(const D3DFrameResource& rhs) = delete;
        D3DFrameResource& operator=(const D3DFrameResource& rhs) = delete;
        ~D3DFrameResource();

    public:
        // We cannot reset the allocator until the GPU is done processing the commands.
        // So each frame needs their own allocator.
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;

        // We cannot update a cbuffer until the GPU is done processing the commands
        // that reference it.  So each frame needs their own cbuffers.
        std::vector<D3DBuffer> constantBuffers;

        // Fence value to mark commands up to this fence point.  This lets us
        // check if these frame resources are still in use by the GPU.
        UINT64 fenceValue = 0;
    };
}