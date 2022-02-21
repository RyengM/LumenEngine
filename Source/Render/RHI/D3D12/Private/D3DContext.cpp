#include "Render/RHI/D3D12/Public/D3DContext.h"

using namespace Lumen::Render;

#ifdef _MSC_VER
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi")
#endif

D3DContext::D3DContext(const WindowInfo& windowInfo)
{
    mDevice = std::make_unique<D3DDevice>();
    
    mGraphicsContext = std::make_unique<D3DCommandContext>(mDevice.get(), EContextType::Graphics, "Graphics");
    mGraphicsBufferPool = std::make_unique<D3DCommandBufferPool>(mDevice.get(), mGraphicsContext.get(), EContextType::Graphics, 256);

    mDsvDescriptorHeap = std::make_unique<D3DDescriptorHeap>(mDevice.get(), EHeapDescriptorType::DSV, 256);
    mRtvDescriptorHeap = std::make_unique<D3DDescriptorHeap>(mDevice.get(), EHeapDescriptorType::RTV, 256);
    mCbvSrvUavDescriptorHeap = std::make_unique<D3DDescriptorHeap>(mDevice.get(), EHeapDescriptorType::CBV_SRV_UAV, 32768);
    mSamplerDescriptorHeap = std::make_unique<D3DDescriptorHeap>(mDevice.get(), EHeapDescriptorType::SAMPLER, 32768);

    mSwapChain = std::make_unique<D3DSwapChain>(mDevice.get(), mGraphicsContext.get(), windowInfo.mainWnd, windowInfo.clientWidth, windowInfo.clientHeight);
    mSwapChain->InitResourceView(mDevice.get(), mRtvDescriptorHeap.get());
}

void D3DContext::BeginFrame()
{
    mGraphicsContext->BeginFrame();
}

void D3DContext::EndFrame()
{
    mGraphicsContext->EndFrame();
}

RHICommandBuffer* D3DContext::RequestCmdBuffer(const EContextType& type, std::string_view name)
{
    // There is only graphics buffer pool now, need to be expanded
    D3DCommandBuffer* cmdBuffer = mGraphicsBufferPool->RequestElement(name);
    cmdBuffer->Clear();
    return cmdBuffer;
}

void D3DContext::ReleaseCmdBuffer(RHICommandBuffer* cmdBuffer)
{
    mGraphicsBufferPool->ReturnElement(static_cast<D3DCommandBuffer*>(cmdBuffer));
}

void D3DContext::ExecuteCmdBuffer(RHICommandBuffer* cmdBuffer)
{
    // There is only graphics buffer pool now, need to be expanded
    mGraphicsContext->ExecuteQueue(cmdBuffer);
}

RHIRenderTargetView* D3DContext::GetBackBufferView()
{
    return mSwapChain->GetCurrentBackBufferView();
}

RHITexture* D3DContext::GetBackBuffer()
{
    return mSwapChain->GetCurrentBuffer();
}

void D3DContext::WaitForGPU()
{

}

void D3DContext::Present()
{
    mSwapChain->Present();
}