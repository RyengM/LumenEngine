#pragma once

#include "D3DDevice.h"
#include "D3DCommandContext.h"
#include "D3DResourceView.h"
#include "Render/RHI/Common/Public/RHISwapChain.h"

namespace Lumen::Render
{
    class D3DSwapChain : public RHISwapChain
    {
    public:
        D3DSwapChain(RHIDevice* rhiDevice, RHICommandContext* rhiCmdContext, void* hWnd, size_t width, size_t height);

        void InitResourceView(RHIDevice* rhiDevice, D3DDescriptorHeap* rtvDescriptorHeap, D3DDescriptorHeap* dsvDescriptorHeap);
        void Resize(RHIDevice* rhiDevice, D3DDescriptorHeap* rtvDescriptorHeap, D3DDescriptorHeap* dsvDescriptorHeap, int width, int height);
        D3DRenderTargetView* GetCurrentBackBufferView();
        D3DTextureResource* GetCurrentBuffer();
        D3DDepthStencilView* GetDepthStencilView();
        D3DTextureResource* GetDepthStencilBuffer();
        void Present();

    private:
        Microsoft::WRL::ComPtr<IDXGISwapChain>              mSwapChain;
        std::unique_ptr<D3DTextureResource>                 mSwapChainBuffer[mSwapChainBufferCount];
        std::unique_ptr<D3DRenderTargetView>                mSwapChainBufferView[mSwapChainBufferCount];
        std::unique_ptr<D3DTextureResource>                 mDepthStencilBuffer;
        std::unique_ptr<D3DDepthStencilView>                mDepthStencilView;
        DXGI_FORMAT                                         mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
        uint32_t                                            mCurBackBufferIndex = 0;
    };
}