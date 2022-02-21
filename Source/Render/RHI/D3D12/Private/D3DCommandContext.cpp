#include "Render/RHI/D3D12/Public/D3DCommandContext.h"
#include "Render/RHI/D3D12/Public/D3DCommandBuffer.h"

using namespace Lumen::Render;

D3DCommandContext::D3DCommandContext(RHIDevice* rhiDevice, EContextType type, std::string_view inName)
{
    name = inName.data() + std::string("_CommandContext");
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);

    fence = std::make_unique<D3DFence>(rhiDevice, inName);

    D3D12_COMMAND_QUEUE_DESC queueDescriptor;
    queueDescriptor.Priority = 0;
    queueDescriptor.NodeMask = 0;
    queueDescriptor.Type = (D3D12_COMMAND_LIST_TYPE)type;
    queueDescriptor.Flags = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE;

    ThrowIfFailed(device->d3dDevice->CreateCommandQueue(&queueDescriptor, IID_PPV_ARGS(&commandQueue)));
    std::string queueName = inName.data() + std::string("_CmdQueue");
    commandQueue->SetName(LPCWSTR(queueName.c_str()));

    for (int i = 0; i < numFrameResource; i++)
        frameResource.push_back(std::make_unique<D3DFrameResource>(device));
}

void D3DCommandContext::ExecuteQueue(RHICommandBuffer* cmdBuffer)
{
    D3DCommandBuffer* buffer = static_cast<D3DCommandBuffer*>(cmdBuffer);
    buffer->Close();
    ID3D12CommandList* cmdsLists[] = { buffer->commandList.Get() };
    commandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
}

void D3DCommandContext::BeginFrame()
{
    currentFrameResourceIndex = (currentFrameResourceIndex + 1) % numFrameResource;
    currentFrameResource = frameResource[currentFrameResourceIndex].get();

    if (currentFrameResource->fenceValue != 0 && fence->d3dFence->GetCompletedValue() < currentFrameResource->fenceValue)
    {
        HANDLE eventHandle = CreateEventEx(nullptr, LPCWSTR(false), false, EVENT_ALL_ACCESS);
        ThrowIfFailed(fence->d3dFence->SetEventOnCompletion(currentFrameResource->fenceValue, eventHandle));
        WaitForSingleObject(eventHandle, INFINITE);
        CloseHandle(eventHandle);
    }

    // Reset allocator when last frame is finished on GPU
    ThrowIfFailed(frameResource[currentFrameResourceIndex]->commandAllocator->Reset());
}

void D3DCommandContext::EndFrame()
{
    currentFrameResource->fenceValue = ++fence->currentFenceValue;
    fence->Signal(this);
}

void D3DCommandContext::FlushQueue()
{
    fence->currentFenceValue++;

    ThrowIfFailed(commandQueue->Signal(fence->d3dFence.Get(), fence->currentFenceValue));

    if (fence->d3dFence->GetCompletedValue() < fence->currentFenceValue)
    {
        HANDLE eventHandle = CreateEventEx(nullptr, LPCWSTR(false), false, EVENT_ALL_ACCESS);
        ThrowIfFailed(fence->d3dFence->SetEventOnCompletion(fence->currentFenceValue, eventHandle));
        WaitForSingleObject(eventHandle, INFINITE);
        CloseHandle(eventHandle);
    }
}