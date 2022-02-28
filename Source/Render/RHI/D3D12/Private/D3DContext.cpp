#include "Render/RHI/D3D12/Public/D3DContext.h"
#include "Game/PlatformFramework/Windows/Public/imgui_impl_dx12.h"

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

    // Allocate an element of srv heap for imgui
    INT offset = mCbvSrvUavDescriptorHeap->RequestElement();
    D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptorHandle = mCbvSrvUavDescriptorHeap->gpuDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
    cpuDescriptorHandle.ptr += offset * mCbvSrvUavDescriptorHeap->descriptorSize;
    D3D12_GPU_DESCRIPTOR_HANDLE gpuDescriptorHandle = mCbvSrvUavDescriptorHeap->gpuDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
    gpuDescriptorHandle.ptr += offset * mCbvSrvUavDescriptorHeap->descriptorSize;
    ImGui_ImplDX12_Init(mDevice->d3dDevice.Get(), mGraphicsContext->numFrameResource, DXGI_FORMAT_R8G8B8A8_UNORM, mCbvSrvUavDescriptorHeap->gpuDescriptorHeap.Get(), cpuDescriptorHandle, gpuDescriptorHandle);
}

void D3DContext::BeginFrame()
{
    mGraphicsContext->BeginFrame();
}

void D3DContext::EndFrame()
{
    mGraphicsContext->EndFrame();
}

RHICommandContext* D3DContext::GetContext(const EContextType& type)
{
    // There is only graphics buffer pool now, need to be expanded
    return mGraphicsContext.get();
}

RHIDescriptorHeap* D3DContext::GetDescriptorHeap(const EHeapDescriptorType& type)
{
    if (type == EHeapDescriptorType::CBV_SRV_UAV)
        return mCbvSrvUavDescriptorHeap.get();
    else if (type == EHeapDescriptorType::DSV)
        return mDsvDescriptorHeap.get();
    else if (type == EHeapDescriptorType::RTV)
        return mRtvDescriptorHeap.get();

    return mSamplerDescriptorHeap.get();
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
    D3DCommandBuffer* buffer = static_cast<D3DCommandBuffer*>(cmdBuffer);
    buffer->Close();
    ID3D12CommandList* cmdsLists[] = { buffer->commandList.Get() };
    mGraphicsContext->commandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
}

RHIRenderTargetView* D3DContext::GetBackBufferView()
{
    return mSwapChain->GetCurrentBackBufferView();
}

RHITexture* D3DContext::GetBackBuffer()
{
    return mSwapChain->GetCurrentBuffer();
}

void D3DContext::Present()
{
    mSwapChain->Present();
}

void D3DContext::CreateGeometry(Mesh* mesh)
{
    auto geometry = std::make_unique<D3DMeshGeometry>();
    geometry->name = mesh->name;

    const UINT vbByteSize = (UINT)mesh->vertices.size() * sizeof(Vertex);
    const UINT ibByteSize = (UINT)mesh->indices.size() * sizeof(unsigned int);

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &geometry->vertexBufferCPU));
    CopyMemory(geometry->vertexBufferCPU->GetBufferPointer(), mesh->vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &geometry->indexBufferCPU));
    CopyMemory(geometry->indexBufferCPU->GetBufferPointer(), mesh->indices.data(), ibByteSize);

    //geometry->vertexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
    //    mCommandList.Get(), vertices.data(), vbByteSize, geo->VertexBufferUploader);

    //geometry->indexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
    //    mCommandList.Get(), indices.data(), ibByteSize, geo->IndexBufferUploader);

    mMeshes[mesh->name] = std::move(geometry);
}