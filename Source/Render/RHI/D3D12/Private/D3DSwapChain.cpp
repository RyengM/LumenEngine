#include "Render/RHI/D3D12/Public/D3DSwapChain.h"

using namespace Lumen::Render;

D3DSwapChain::D3DSwapChain(RHIDevice* rhiDevice, RHICommandContext* rhiCmdContext, void* hWnd, size_t width, size_t height)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);
    D3DCommandContext* cmdContext = static_cast<D3DCommandContext*>(rhiCmdContext);

    DXGI_SWAP_CHAIN_DESC descriptor;
    {
        descriptor.BufferDesc.Width                     = width;
        descriptor.BufferDesc.Height                    = height;
        descriptor.BufferDesc.RefreshRate.Numerator     = 60;
        descriptor.BufferDesc.RefreshRate.Denominator   = 1;
        descriptor.BufferDesc.Format                    = mBackBufferFormat;
        descriptor.BufferDesc.ScanlineOrdering          = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        descriptor.BufferDesc.Scaling                   = DXGI_MODE_SCALING_UNSPECIFIED;
        descriptor.SampleDesc.Count                     = 1;
        descriptor.SampleDesc.Quality                   = 0;
        descriptor.BufferUsage                          = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        descriptor.BufferCount                          = mSwapChainBufferCount;
        descriptor.OutputWindow                         = (HWND)hWnd;
        descriptor.Windowed                             = true;
        descriptor.SwapEffect                           = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        descriptor.Flags                                = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    }

    ThrowIfFailed(device->dxgiFactory->CreateSwapChain(cmdContext->commandQueue.Get(), &descriptor, mSwapChain.GetAddressOf()));

    TextureDescriptor texDescriptor;
    {
        texDescriptor.width = (int)width;
        texDescriptor.height = (int)height;
        texDescriptor.slices = 1;
        texDescriptor.sparse = false;
        texDescriptor.mipLevel = 1;
        texDescriptor.anisoLevel = 1;
        texDescriptor.sample = EMSAASample::None;
        texDescriptor.usageType = EUsageType::RenderTarget;
        texDescriptor.textureType = ETextureType::Tex2D;
        texDescriptor.storageType = EStorageType::Default;
        texDescriptor.format = EGraphicsFormat::R8G8B8A8_UNorm;
    }

    for (int i = 0; i < mSwapChainBufferCount; i++)
    {
        mSwapChainBuffer[i] = std::make_unique<D3DTexture>();
        mSwapChainBuffer[i]->descriptor = texDescriptor;
        ThrowIfFailed(mSwapChain->GetBuffer(i, IID_PPV_ARGS(&mSwapChainBuffer[i]->defaultResource)));
    }
}

void D3DSwapChain::InitResourceView(RHIDevice* rhiDevice, D3DDescriptorHeap* descriptorHeap)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);

    for (int i = 0; i < mSwapChainBufferCount; i++)
        mSwapChainBufferView[i] = std::make_unique<D3DRenderTargetView>(rhiDevice, descriptorHeap, mSwapChainBuffer[i].get());
}

D3DRenderTargetView* D3DSwapChain::GetCurrentBackBufferView()
{
    return mSwapChainBufferView[mCurBackBufferIndex].get();
}

D3DTexture* D3DSwapChain::GetCurrentBuffer()
{
    return mSwapChainBuffer[mCurBackBufferIndex].get();
}

void D3DSwapChain::Present()
{
    ThrowIfFailed(mSwapChain->Present(1, 0));
    mCurBackBufferIndex = (mCurBackBufferIndex + 1) % mSwapChainBufferCount;
}