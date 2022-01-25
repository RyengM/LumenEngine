#pragma once
#include "Render/RHI/Common/Public/GraphicsRHI.h"
#include "Render/RHI/D3D12/Public/D3DUtil.h"
#include "Render/RHI/D3D12/Public/FrameResource.h"
#include "Game/PlatformFramework/Windows/Public/imgui_impl_dx12.h"

namespace Lumen::Render
{
    struct FrameContext
    {
        ID3D12CommandAllocator* CommandAllocator;
        UINT64                  FenceValue;
    };

    class D3D12GraphicsRHI : public GraphicsRHI
    {
    public:
        // Invoked at the start of render frame, wait for GPU fence
        virtual void NewFrame() override;
        // Invoked at the end of render frame, swap buffer and set a new fence point
        virtual void EndFrame() override;
        // Resize swapchain buffer
        virtual void OnResize() override;

        // UI related
        virtual void InitUI() override;
        virtual void DrawUI(void* drawData) override;
        virtual void CreateUIDeviceObject() override;

        // Backend specified
        virtual bool InitDirect3D(void* hWnd) override;
        virtual void SetClientResolution(int width, int height) override;
        // Wait until frame commands are complete
        virtual void FlushCommandQueue() override;

    private:
        void CreateCommandObjects();
        void CreateSwapChain(void* hWnd);
        void CreateRtvAndDsvDescriptorHeaps();
        
        void LogAdapters();
        void LogAdapterOutputs(IDXGIAdapter* adapter);
        void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

        void BuildFrameResources();

        ID3D12Resource* GetCurrentBackBuffer() const;
        D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView() const;
        D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const;

    private:
        static int const mNumFrameInFlight    = 3;

        // Render should be started after device is prepared, it will be set true at second frame
        bool bDevicePrepared = false;
        bool bFirstFrame = true;

        // MSAA config, used in PSO setup
        bool      m4xMsaaState = false;
        UINT      m4xMsaaQuality = 0;

        Microsoft::WRL::ComPtr<IDXGIFactory4>                   mDxgiFactory;
        Microsoft::WRL::ComPtr<IDXGISwapChain>                  mSwapChain;
        Microsoft::WRL::ComPtr<ID3D12Device>                    mD3dDevice;
        Microsoft::WRL::ComPtr<ID3D12CommandQueue>              mCommandQueue;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>       mCommandList;

        std::vector<std::unique_ptr<FrameResource>>             mFrameResources;
        FrameResource*                                          mCurrFrameResource = nullptr;
        UINT                                                    mCurrFrameResourceIndex = 0;

        Microsoft::WRL::ComPtr<ID3D12Fence>                     mFence;
        UINT64                                                  mCurrentFence = 0;        

        static const int                                        SwapChainBufferCount = 2;
        int                                                     mCurrBackBuffer = 0;
        Microsoft::WRL::ComPtr<ID3D12Resource>                  mSwapChainBuffer[SwapChainBufferCount];
        Microsoft::WRL::ComPtr<ID3D12Resource>                  mDepthStencilBuffer;

        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>            mRtvHeap;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>            mDsvHeap;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>            mSrvHeap;

        UINT                                                    mRtvDescriptorSize = 0;
        UINT                                                    mDsvDescriptorSize = 0;
        UINT                                                    mCbvSrvUavDescriptorSize = 0;

        D3D_DRIVER_TYPE                                         mD3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
        DXGI_FORMAT                                             mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
        DXGI_FORMAT                                             mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

        D3D12_VIEWPORT                                          mScreenViewport;
        D3D12_RECT                                              mScissorRect;

        int                                                     mClientWidth = 0;
        int                                                     mClientHeight = 0;
    };
}

