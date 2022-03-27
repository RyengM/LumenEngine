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
    mSwapChain->InitResourceView(mDevice.get(), mRtvDescriptorHeap.get(), mDsvDescriptorHeap.get());

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

void D3DContext::Present()
{
    mSwapChain->Present();
}

void D3DContext::Prepare()
{
    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(mSwapChain->GetDepthStencilBuffer()->defaultResource.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE);

    auto cmdBuffer = static_cast<D3DCommandBuffer*>(RequestCmdBuffer(EContextType::Graphics, "PrepareRender"));
    auto cmdList = cmdBuffer->commandList;

    // Change depth buffer state to depth write
    cmdList->ResourceBarrier(1, &barrier);

    ExecuteCmdBuffer(cmdBuffer);
    ReleaseCmdBuffer(cmdBuffer);
}

void D3DContext::UpdatePassCB(const Camera& camera)
{
    auto passCB = mGraphicsContext->currentFrameResource->passBuffers.get();
    PassConstants constants;
    XMStoreFloat4x4(&constants.viewProj, MathHelper::ConvertToDxMatrix(camera.GetViewProjMatrix()));
    passCB->SetData<PassConstants>(0, constants, true);
}

void D3DContext::RenderScene()
{
    CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(mSwapChain->GetCurrentBuffer()->defaultResource.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(mSwapChain->GetCurrentBuffer()->defaultResource.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

    auto cmdBuffer = static_cast<D3DCommandBuffer*>(RequestCmdBuffer(EContextType::Graphics, "RenderScene"));
    auto cmdList = cmdBuffer->commandList;

    auto pso = mPSOs.at("SimpleForward").get();
    auto geo = mMeshes.at("box").get();
    auto frameResource = mGraphicsContext->currentFrameResource;

    cmdList->Close();
    //ThrowIfFailed(frameResource->commandAllocator->Reset());
    ThrowIfFailed(cmdList->Reset(frameResource->commandAllocator.Get(), pso->d3dPso.Get()));

    D3D12_VIEWPORT mScreenViewport;
    mScreenViewport.TopLeftX = 0;
    mScreenViewport.TopLeftY = 0;
    mScreenViewport.Width = static_cast<float>(1920);
    mScreenViewport.Height = static_cast<float>(1080);
    mScreenViewport.MinDepth = 0.0f;
    mScreenViewport.MaxDepth = 1.0f;
    D3D12_RECT mScissorRect = { 0, 0, 1920, 1080 };
    cmdList->RSSetViewports(1, &mScreenViewport);
    cmdList->RSSetScissorRects(1, &mScissorRect);

    cmdList->ResourceBarrier(1, &beforeBarrier);

    const float clearColor[4] = { 0.9f, 0.3f, 0.5f, 1.0f };
    cmdList->ClearRenderTargetView(mSwapChain->GetCurrentBackBufferView()->descriptorHandle, clearColor, 0, nullptr);
    cmdList->ClearDepthStencilView(mSwapChain->GetDepthStencilView()->descriptorHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.f, 0, 0, nullptr);

    cmdList->OMSetRenderTargets(1, &mSwapChain->GetCurrentBackBufferView()->descriptorHandle, true, &mSwapChain->GetDepthStencilView()->descriptorHandle);
    ID3D12DescriptorHeap* descriptorHeaps[] = { mCbvSrvUavDescriptorHeap->gpuDescriptorHeap.Get() };
    cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

    cmdList->SetGraphicsRootSignature(pso->rootSignature.Get());

    auto vBufferView = geo->VertexBufferView();
    auto iBufferView = geo->IndexBufferView();
    cmdList->IASetVertexBuffers(0, 1, &vBufferView);
    cmdList->IASetIndexBuffer(&iBufferView);
    cmdList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    cmdList->SetGraphicsRootConstantBufferView(0, frameResource->passBuffers->uploadResource->GetGPUVirtualAddress());
    cmdList->DrawIndexedInstanced(geo->indexCount, 1, 0, 0, 0);
    cmdList->ResourceBarrier(1, &afterBarrier);

    ExecuteCmdBuffer(cmdBuffer);
    ReleaseCmdBuffer(cmdBuffer);
}

void D3DContext::CreateVisualBuffer(VisualBuffer* buffer)
{
    TextureDescriptor desc;
    {
        desc.width = (int)800;
        desc.height = (int)600;
        desc.slices = 1;
        desc.sparse = false;
        desc.mipLevel = 1;
        desc.anisoLevel = 1;
        desc.sample = EMSAASample::None;
        desc.usageType = EUsageType::RenderTarget;
        desc.textureType = ETextureType::Tex2D;
        desc.storageType = EStorageType::Default;
        desc.format = EGraphicsFormat::R8G8B8A8_UNorm;
    }
    auto tex = std::make_unique<D3DTexture>(mDevice.get(), desc);

    buffer->srv = std::make_unique<D3DShaderResourceView>(mDevice.get(), mCbvSrvUavDescriptorHeap.get(), tex.get());
    buffer->rtv = std::make_unique<D3DRenderTargetView>(mDevice.get(), mRtvDescriptorHeap.get(), tex.get());
    buffer->srvHandle = buffer->srv->gpuAddress;
    buffer->rtvHandle = buffer->rtv->gpuAddress;

    mTextures[buffer->name] = std::move(tex);
}

// No obj load version
void D3DContext::CreateGeometry(RHICommandBuffer* cmdBuffer, const Mesh& mesh)
{
    D3DCommandBuffer* cmdList = static_cast<D3DCommandBuffer*>(cmdBuffer);

    auto geometry = std::make_unique<D3DMeshGeometry>();
    geometry->name = mesh.name;

    std::array<Vertex, 8> vertices =
    {
        Vertex(Float3(-1.f, -1.f, -1.f)),
        Vertex(Float3(-1.f, +1.f, -1.f)),
        Vertex(Float3(+1.f, +1.f, -1.f)),
        Vertex(Float3(+1.f, -1.f, -1.f)),
        Vertex(Float3(-1.f, -1.f, +1.f)),
        Vertex(Float3(-1.f, +1.f, +1.f)),
        Vertex(Float3(+1.f, +1.f, +1.f)),
        Vertex(Float3(+1.f, -1.f, +1.f))
    };

    std::array<std::uint16_t, 36> indices =
    {
        // front face
        0, 1, 2,
        0, 2, 3,

        // back face
        4, 6, 5,
        4, 7, 6,

        // left face
        4, 5, 1,
        4, 1, 0,

        // right face
        3, 2, 6,
        3, 6, 7,

        // top face
        1, 5, 6,
        1, 6, 2,

        // bottom face
        4, 0, 3,
        4, 3, 7
    };

    const UINT vbByteSize = (UINT)vertices.size() * sizeof(Vertex);
    const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);

    geometry->vertexByteStride = sizeof(Vertex);
    geometry->vertexBufferByteSize = vbByteSize;
    geometry->indexFormat = DXGI_FORMAT_R16_UINT;
    geometry->indexBufferByteSize = ibByteSize;
    geometry->indexCount = indices.size();

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &geometry->vertexBufferCPU));
    CopyMemory(geometry->vertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &geometry->indexBufferCPU));
    CopyMemory(geometry->indexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

    // Create resource buffer and upload buffer
    BufferDescriptor desc;
    {
        desc.name = mesh.name;
        desc.count = vertices.size();
        desc.stride = sizeof(Vertex);
        desc.usageType = EUsageType::Default;
        desc.bufferType = EBufferType::Vertex;
        desc.storageType = EStorageType((uint32_t)EStorageType::Static | (uint32_t)EStorageType::Default);
    };
    geometry->vertexBufferGPU = std::make_unique<D3DBuffer>(mDevice.get(), desc);
    {
        desc.count = indices.size();
        desc.stride = sizeof(std::uint16_t);
        desc.bufferType = EBufferType::Index;
    }
    geometry->indexBufferGPU = std::make_unique<D3DBuffer>(mDevice.get(), desc);

    // Copy data from upload buffer to default buffer
    {   // Vertex
        D3D12_SUBRESOURCE_DATA subResourceData = {};
        subResourceData.pData = vertices.data();
        subResourceData.RowPitch = vbByteSize;
        subResourceData.SlicePitch = subResourceData.RowPitch;

        CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->vertexBufferGPU->defaultResource.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
        CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->vertexBufferGPU->defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);

        cmdList->commandList->ResourceBarrier(1, &beforeBarrier);
        UpdateSubresources<1>(cmdList->commandList.Get(), geometry->vertexBufferGPU->defaultResource.Get(), geometry->vertexBufferGPU->uploadResource.Get(), 0, 0, 1, &subResourceData);
        cmdList->commandList->ResourceBarrier(1, &afterBarrier);
    }
    {   // Index
        D3D12_SUBRESOURCE_DATA subResourceData = {};
        subResourceData.pData = indices.data();
        subResourceData.RowPitch = ibByteSize;
        subResourceData.SlicePitch = subResourceData.RowPitch;

        CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->indexBufferGPU->defaultResource.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
        CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->indexBufferGPU->defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);

        cmdList->commandList->ResourceBarrier(1, &beforeBarrier);
        UpdateSubresources<1>(cmdList->commandList.Get(), geometry->indexBufferGPU->defaultResource.Get(), geometry->indexBufferGPU->uploadResource.Get(), 0, 0, 1, &subResourceData);
        cmdList->commandList->ResourceBarrier(1, &afterBarrier);
    }

    mMeshes[mesh.name] = std::move(geometry);
}

//void D3DContext::CreateGeometry(RHICommandBuffer* cmdBuffer, const Mesh& mesh)
//{
//    D3DCommandBuffer* cmdList = static_cast<D3DCommandBuffer*>(cmdBuffer);
//
//    auto geometry = std::make_unique<D3DMeshGeometry>();
//    geometry->name = mesh.name;
//
//    const UINT vbByteSize = (UINT)mesh.vertices.size() * sizeof(Vertex);
//    const UINT ibByteSize = (UINT)mesh.indices.size() * sizeof(std::uint16_t);
//
//    geometry->vertexByteStride = sizeof(Vertex);
//    geometry->vertexBufferByteSize = vbByteSize;
//    geometry->indexBufferByteSize = ibByteSize;
//
//    ThrowIfFailed(D3DCreateBlob(vbByteSize, &geometry->vertexBufferCPU));
//    CopyMemory(geometry->vertexBufferCPU->GetBufferPointer(), mesh.vertices.data(), vbByteSize);
//
//    ThrowIfFailed(D3DCreateBlob(ibByteSize, &geometry->indexBufferCPU));
//    CopyMemory(geometry->indexBufferCPU->GetBufferPointer(), mesh.indices.data(), ibByteSize);
//
//    // Create resource buffer
//    BufferDescriptor desc;
//    {
//        desc.name = mesh.name;
//        desc.count = (UINT)mesh.vertices.size();
//        desc.stride = sizeof(Vertex);
//        desc.usageType = EUsageType::Default;
//        desc.bufferType = EBufferType::Vertex;
//        desc.storageType = EStorageType((uint32_t)EStorageType::Static | (uint32_t)EStorageType::Default);
//    };
//    geometry->vertexBufferGPU = std::make_unique<D3DBuffer>(mDevice.get(), desc);
//    {
//        desc.count = (UINT)mesh.indices.size();
//        desc.stride = sizeof(uint16_t);
//        desc.bufferType = EBufferType::Index;
//    }
//    geometry->indexBufferGPU = std::make_unique<D3DBuffer>(mDevice.get(), desc);
//
//    // Copy data from upload buffer to default buffer
//    {   // Vertex
//        D3D12_SUBRESOURCE_DATA subResourceData = {};
//        subResourceData.pData = mesh.vertices.data();
//        subResourceData.RowPitch = vbByteSize;
//        subResourceData.SlicePitch = subResourceData.RowPitch;
//
//        CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->vertexBufferGPU->defaultResource.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
//        CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->vertexBufferGPU->defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
//
//        cmdList->commandList->ResourceBarrier(1, &beforeBarrier);
//        UpdateSubresources<1>(cmdList->commandList.Get(), geometry->vertexBufferGPU->defaultResource.Get(), geometry->vertexBufferGPU->uploadResource.Get(), 0, 0, 1, &subResourceData);
//        cmdList->commandList->ResourceBarrier(1, &afterBarrier);
//    }
//    {   // Index
//        D3D12_SUBRESOURCE_DATA subResourceData = {};
//        subResourceData.pData = mesh.indices.data();
//        subResourceData.RowPitch = ibByteSize;
//        subResourceData.SlicePitch = subResourceData.RowPitch;
//
//        CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->indexBufferGPU->defaultResource.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
//        CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->indexBufferGPU->defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
//
//        cmdList->commandList->ResourceBarrier(1, &beforeBarrier);
//        UpdateSubresources<1>(cmdList->commandList.Get(), geometry->indexBufferGPU->defaultResource.Get(), geometry->indexBufferGPU->uploadResource.Get(), 0, 0, 1, &subResourceData);
//        cmdList->commandList->ResourceBarrier(1, &afterBarrier);
//    }
//
//    mMeshes[mesh.name] = std::move(geometry);
//}

void D3DContext::CreateShaders(const ShaderLab& shaderlab)
{
    for (auto kernel : shaderlab.category.kernels)
    {
        auto shader = std::make_unique<D3DShader>(kernel.hlsl);
        auto pso = std::make_unique<D3DPipelineState>(mDevice.get(), kernel.tags.at("Name"), &kernel, shader.get());
        mShaders[kernel.tags.at("Name")] = std::move(shader);
        mPSOs[kernel.tags.at("Name")] = std::move(pso);
    }
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

RHIRenderTargetView* D3DContext::GetBackBufferView()
{
    return mSwapChain->GetCurrentBackBufferView();
}

RHITexture* D3DContext::GetBackBuffer()
{
    return mSwapChain->GetCurrentBuffer();
}

RHIDepthStencilView* D3DContext::GetBackDepthStencilView()
{
    return mSwapChain->GetDepthStencilView();
}