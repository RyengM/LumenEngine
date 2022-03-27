#include "Render/RHI/D3D12/Public/D3DCommandBuffer.h"
#include "Render/RHI/D3D12/Public/D3DPipelineState.h"
#include "Game/PlatformFramework/Windows/Public/imgui_impl_dx12.h"

using namespace Lumen::Render;

D3DCommandBuffer::D3DCommandBuffer(RHIDevice* rhiDevice, RHICommandContext* rhiContext, EContextType inContextType)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);
    D3DCommandContext* commandContext = static_cast<D3DCommandContext*>(rhiContext);

    contextType = inContextType;
    commandAllocator = commandContext->frameResource[0]->commandAllocator;

    ThrowIfFailed(device->d3dDevice->CreateCommandList(0, (D3D12_COMMAND_LIST_TYPE)inContextType,
        commandAllocator.Get(), nullptr, IID_PPV_ARGS(commandList.GetAddressOf())));

    commandList->Close();
}

void D3DCommandBuffer::Clear()
{
    bClose = false;
    ThrowIfFailed(commandList->Reset(commandAllocator.Get(), nullptr));
}

void D3DCommandBuffer::Close()
{
    if (bClose) return;

    bClose = true;
    ThrowIfFailed(commandList->Close());
}

void D3DCommandBuffer::ClearRenderTarget(RHITexture* texture, RHIRenderTargetView* rtvView, const Vec4& color)
{
    D3DRenderTargetView* view = static_cast<D3DRenderTargetView*>(rtvView);
    D3DTexture* resource = static_cast<D3DTexture*>(texture);
    const float clearColor[4] = { color.x, color.y, color.z, color.w };

    CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(resource->defaultResource.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(resource->defaultResource.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    
    commandList->ResourceBarrier(1, &beforeBarrier);
    commandList->ClearRenderTargetView(view->descriptorHandle, clearColor, 0, nullptr);
    commandList->ResourceBarrier(1, &afterBarrier);
}

void D3DCommandBuffer::DrawUI(RHIDescriptorHeap* rhiHeap, RHITexture* texture, RHIRenderTargetView* rtvView, void* data)
{
    D3DDescriptorHeap* heap = static_cast<D3DDescriptorHeap*>(rhiHeap);
    D3DRenderTargetView* view = static_cast<D3DRenderTargetView*>(rtvView);
    D3DTexture* resource = static_cast<D3DTexture*>(texture);

    const float clearColor[4] = { 0.2, 0.3, 0.4, 1.0 };

    CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(resource->defaultResource.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(resource->defaultResource.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

    commandList->ResourceBarrier(1, &beforeBarrier);
    commandList->ClearRenderTargetView(view->descriptorHandle, clearColor, 0, nullptr);
    commandList->OMSetRenderTargets(1, &view->descriptorHandle, FALSE, NULL);

    ID3D12DescriptorHeap* descriptorHeaps[] = { heap->gpuDescriptorHeap.Get()};
    commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

    ImGui_ImplDX12_RenderDrawData(static_cast<ImDrawData*>(data), commandList.Get());
    commandList->ResourceBarrier(1, &afterBarrier);
}

void D3DCommandBuffer::DrawIndexed(RHIResource* rhiResource, RHIRenderTargetView* rhiRtvView, RHIDepthStencilView* rhiDsvView, RHIDescriptorHeap* rhiHeap, RHIPipelineState* rhiPso, RHIMeshGeometry* rhiGeo)
{
    //D3DTexture* resource = static_cast<D3DTexture*>(rhiResource);
    //D3DRenderTargetView* rtvView = static_cast<D3DRenderTargetView*>(rhiRtvView);
    //D3DDepthStencilView* dsvView = static_cast<D3DDepthStencilView*>(rhiDsvView);
    //D3DDescriptorHeap* heap = static_cast<D3DDescriptorHeap*>(rhiHeap);
    //D3DPipelineState* pso = static_cast<D3DPipelineState*>(rhiPso);
    //D3DMeshGeometry* geo = static_cast<D3DMeshGeometry*>(rhiGeo);

    //CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(resource->defaultResource.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    //CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(resource->defaultResource.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

    //commandList->Close();
    //ThrowIfFailed(commandList->Reset(commandAllocator.Get(), pso->d3dPso.Get()));

    //D3D12_VIEWPORT mScreenViewport;
    //mScreenViewport.TopLeftX = 0;
    //mScreenViewport.TopLeftY = 0;
    //mScreenViewport.Width = static_cast<float>(1920);
    //mScreenViewport.Height = static_cast<float>(1080);
    //mScreenViewport.MinDepth = 0.0f;
    //mScreenViewport.MaxDepth = 1.0f;
    //D3D12_RECT mScissorRect = { 0, 0, 1920, 1080 };
    //commandList->RSSetViewports(1, &mScreenViewport);
    //commandList->RSSetScissorRects(1, &mScissorRect);

    //commandList->ResourceBarrier(1, &beforeBarrier);
    //commandList->OMSetRenderTargets(1, &rtvView->descriptorHandle, true, &dsvView->descriptorHandle);
    //ID3D12DescriptorHeap* descriptorHeaps[] = { heap->gpuDescriptorHeap.Get()};
    //commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

    //commandList->SetGraphicsRootSignature(pso->rootSignature.Get());

    //auto vBufferView = geo->VertexBufferView();
    //auto iBufferView = geo->IndexBufferView();
    //commandList->IASetVertexBuffers(0, 1, &vBufferView);
    //commandList->IASetIndexBuffer(&iBufferView);
    //commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    //commandList->SetGraphicsRootDescriptorTable(0, heap->gpuDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
    //commandList->DrawIndexedInstanced(geo->indexBufferByteSize, 1, 0, 0, 0);
    //commandList->ResourceBarrier(1, &afterBarrier);
}

D3DCommandBufferPool::D3DCommandBufferPool(RHIDevice* rhiDevice, RHICommandContext* rhiContext, EContextType inContextType, size_t capacity)
{
    ownerContext = static_cast<D3DCommandContext*>(rhiContext);
    mCmdBuffers.resize(capacity, D3DCommandBuffer(rhiDevice, rhiContext, inContextType));
    mFreeElements.resize(capacity);
    for (int i = 0; i < capacity; i++)
    {
        mFreeElements[i] = i;
        mCmdBuffers[i].indexInPool = i;
    }
}

D3DCommandBuffer* D3DCommandBufferPool::RequestElement(std::string_view name)
{
    //if (!mFreeElements.size()) Expand();

    size_t index = mFreeElements.back();
    mFreeElements.pop_back();
    D3DCommandBuffer* buffer = &mCmdBuffers[index];
    buffer->commandAllocator = ownerContext->currentFrameResource->commandAllocator;
    return buffer;;
}

void D3DCommandBufferPool::ReturnElement(D3DCommandBuffer* cmdBuffer)
{
    cmdBuffer->Close();
    mFreeElements.push_back(cmdBuffer->indexInPool);
}