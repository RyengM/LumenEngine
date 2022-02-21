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

        void InitResourceView(RHIDevice* rhiDevice, D3DDescriptorHeap* descriptorHeap);
        D3DRenderTargetView* GetCurrentBackBufferView();
        D3DTexture* GetCurrentBuffer();
        void Present();

    private:
        Microsoft::WRL::ComPtr<IDXGISwapChain>              mSwapChain;
        std::unique_ptr<D3DTexture>                         mSwapChainBuffer[mSwapChainBufferCount];
        std::unique_ptr<D3DRenderTargetView>                mSwapChainBufferView[mSwapChainBufferCount];
        DXGI_FORMAT                                         mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
        int                                                 mCurBackBufferIndex = 0;
    };
}