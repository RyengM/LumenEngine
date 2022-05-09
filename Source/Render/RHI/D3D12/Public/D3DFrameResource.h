#pragma once

#include "D3DResource.h"
#include "MathHelper.h"

namespace Lumen::Render
{
    #define MAX_LIGHTS 6

    struct ObjectConstants
    {
        DirectX::XMFLOAT4X4 model = MathHelper::Identity4x4();
    };

    struct PassConstants
    {
        DirectX::XMFLOAT4X4 view = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 invView = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 proj = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 invProj = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 viewProj = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 invViewProj = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 viewProjTex = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 shadowTransform = MathHelper::Identity4x4();
        DirectX::XMFLOAT3 eyePosW = { 0.0f, 0.0f, 0.0f };
        float cbPerObjectPad1 = 0.0f;
        DirectX::XMFLOAT2 renderTargetSize = { 0.0f, 0.0f };
        DirectX::XMFLOAT2 invRenderTargetSize = { 0.0f, 0.0f };
        float nearZ = 0.0f;
        float farZ = 0.0f;
        float totalTime = 0.0f;
        float deltaTime = 0.0f;

        DirectX::XMFLOAT4 ambientLight = { 0.0f, 0.0f, 0.0f, 1.0f };

        D3DLight light[MAX_LIGHTS];
    };

    // Stores the resources needed for the CPU to build the command lists for a frame.  
    struct D3DFrameResource
    {
    public:

        D3DFrameResource(RHIDevice* rhiDevice);
        D3DFrameResource(const D3DFrameResource& rhs) = delete;
        D3DFrameResource& operator=(const D3DFrameResource& rhs) = delete;
        ~D3DFrameResource();

    private:
        // Constant buffer elements need to be multiples of 256 bytes.
        size_t CalcStride(size_t stride);

    public:
        // We cannot reset the allocator until the GPU is done processing the commands.
        // So each frame needs their own allocator.
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;

        // We cannot update a cbuffer until the GPU is done processing the commands
        // that reference it.  So each frame needs their own cbuffers.
        std::unique_ptr<D3DBufferResource> passBuffers;
        std::unique_ptr<D3DBufferResource> objectBuffers;
        std::unique_ptr<D3DBufferResource> materialBuffers;

        // Fence value to mark commands up to this fence point.  This lets us
        // check if these frame resources are still in use by the GPU.
        UINT64 fenceValue = 0;
    };
}