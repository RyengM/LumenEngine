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