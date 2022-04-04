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

    // Allocate an element of srv heap for imgui: font
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

void D3DContext::UpdateObjectCB(const std::vector<Entity>& entities)
{
    auto objectCB = mGraphicsContext->currentFrameResource->objectBuffers.get();

    for (auto entity : entities)
    {
        ObjectConstants constants;

        Mat4 world = Mat4(1.f).Scale(entity.GetTransform()->scale).Translate(entity.GetTransform()->position);
        DirectX::XMMATRIX model = MathHelper::ConvertToDxMatrix(world);
        XMStoreFloat4x4(&constants.model, model);

        auto item = mRenderItems[entity.GetName()].get();
        item->world = constants.model;
        objectCB->SetData<ObjectConstants>(item->objectCBIndex, constants, true);
    }
}

void D3DContext::UpdatePassCB(const Camera& camera, const DirectionalLight& light)
{
    auto passCB = mGraphicsContext->currentFrameResource->passBuffers.get();
    PassConstants constants;

    DirectX::XMMATRIX view = MathHelper::ConvertToDxMatrix(camera.GetViewMatrix());
    DirectX::XMMATRIX proj = MathHelper::ConvertToDxMatrix(camera.GetProjMatrix());
    DirectX::XMMATRIX viewProj = XMMatrixMultiply(view, proj);
    DirectX::XMVECTOR viewDet = XMMatrixDeterminant(view);
    DirectX::XMVECTOR projDet = XMMatrixDeterminant(proj);
    DirectX::XMVECTOR viewProjDet = XMMatrixDeterminant(viewProj);
    DirectX::XMMATRIX invView = XMMatrixInverse(&viewDet, view);
    DirectX::XMMATRIX invProj = XMMatrixInverse(&projDet, proj);
    DirectX::XMMATRIX invViewProj = XMMatrixInverse(&viewProjDet, viewProj);
    // Transform NDC space [-1,+1]^2 to texture space [0,1]^2
    DirectX::XMMATRIX T(
        0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f);

    DirectX::XMMATRIX viewProjTex = XMMatrixMultiply(viewProj, T);

    XMStoreFloat4x4(&constants.view, view);
    XMStoreFloat4x4(&constants.invView, invView);
    XMStoreFloat4x4(&constants.proj, proj);
    XMStoreFloat4x4(&constants.invProj,invProj);
    XMStoreFloat4x4(&constants.viewProj, viewProj);
    XMStoreFloat4x4(&constants.invViewProj, invViewProj);
    constants.eyePosW = MathHelper::ConvertToDxFloat3(camera.GetPos());
    constants.nearZ = camera.GetNearZ();
    constants.farZ = camera.GetFarZ();
    constants.ambientLight = { 0.4f, 0.4f, 0.6f, 1.0f };
    constants.light[0].position = MathHelper::ConvertToDxFloat3(light.GetPosition());
    constants.light[0].direction = MathHelper::ConvertToDxFloat3(light.GetDirection());
    constants.light[0].strength = MathHelper::ConvertToDxFloat3(light.strength);

    passCB->SetData<PassConstants>(0, constants, true);
}

void D3DContext::RenderScene(uint32_t width, uint32_t height)
{
    CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(mSceneRT->colorBuffer->resource->defaultResource.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);
    CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(mSceneRT->colorBuffer->resource->defaultResource.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

    auto cmdBuffer = static_cast<D3DCommandBuffer*>(RequestCmdBuffer(EContextType::Graphics, "RenderScene"));
    auto cmdList = cmdBuffer->commandList;

    auto pso = mPSOs.at("SimpleForward").get();
    auto frameResource = mGraphicsContext->currentFrameResource;

    cmdList->Close();
    ThrowIfFailed(cmdList->Reset(frameResource->commandAllocator.Get(), pso->d3dPso.Get()));

    D3D12_VIEWPORT mScreenViewport;
    mScreenViewport.TopLeftX = 0;
    mScreenViewport.TopLeftY = 0;
    mScreenViewport.Width = static_cast<float>(width);
    mScreenViewport.Height = static_cast<float>(height);
    mScreenViewport.MinDepth = 0.0f;
    mScreenViewport.MaxDepth = 1.0f;
    D3D12_RECT mScissorRect = { 0, 0, (LONG)width, (LONG)height };
    cmdList->RSSetViewports(1, &mScreenViewport);
    cmdList->RSSetScissorRects(1, &mScissorRect);

    cmdList->ResourceBarrier(1, &beforeBarrier);

    const float clearColor[4] = { 0, 0, 0, 0 };
    cmdList->ClearRenderTargetView(mSceneRT->colorBuffer->rtvView->descriptorHandle, clearColor, 0, nullptr);
    cmdList->ClearDepthStencilView(mSceneRT->depthBuffer->dsvView->descriptorHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.f, 0, 0, nullptr);

    cmdList->OMSetRenderTargets(1, &mSceneRT->colorBuffer->rtvView->descriptorHandle, true, &mSceneRT->depthBuffer->dsvView->descriptorHandle);
    ID3D12DescriptorHeap* descriptorHeaps[] = { mCbvSrvUavDescriptorHeap->gpuDescriptorHeap.Get() };
    cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

    cmdList->SetGraphicsRootSignature(pso->rootSignature.Get());

    cmdList->SetGraphicsRootConstantBufferView(1, frameResource->passBuffers->uploadResource->GetGPUVirtualAddress());
    DrawRenderTargets(cmdList.Get());
    cmdList->ResourceBarrier(1, &afterBarrier);

    ExecuteCmdBuffer(cmdBuffer);
    ReleaseCmdBuffer(cmdBuffer);
}

void D3DContext::DrawRenderTargets(ID3D12GraphicsCommandList* cmdList)
{
    for (auto& item : mRenderItems)
    {
        auto geo = item.second->mesh;

        auto vBufferView = geo->VertexBufferView();
        auto iBufferView = geo->IndexBufferView();
        cmdList->IASetVertexBuffers(0, 1, &vBufferView);
        cmdList->IASetIndexBuffer(&iBufferView);
        cmdList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        D3D12_GPU_VIRTUAL_ADDRESS objectCBAddress = mGraphicsContext->currentFrameResource->objectBuffers->uploadResource->GetGPUVirtualAddress();
        cmdList->SetGraphicsRootConstantBufferView(0, objectCBAddress + item.second->objectCBIndex * ((sizeof(ObjectConstants) + 255) & ~255));
        cmdList->SetGraphicsRootDescriptorTable(3, mTextures.at("boxBaseColor")->srvView->gpuDescriptorHandleGPU);
        cmdList->DrawIndexedInstanced(geo->indexCount, 1, 0, 0, 0);
    }
}

void D3DContext::DrawUI(void* data)
{
    auto cmdBuffer = static_cast<D3DCommandBuffer*>(RequestCmdBuffer(EContextType::Graphics, "RenderScene"));
    auto cmdList = cmdBuffer->commandList;

    const float clearColor[4] = { 0.2, 0.3, 0.4, 1.0 };

    CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(mSwapChain->GetCurrentBuffer()->defaultResource.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(mSwapChain->GetCurrentBuffer()->defaultResource.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

    cmdList->ResourceBarrier(1, &beforeBarrier);
    cmdList->ClearRenderTargetView(mSwapChain->GetCurrentBackBufferView()->descriptorHandle, clearColor, 0, nullptr);
    cmdList->ClearDepthStencilView(mSwapChain->GetDepthStencilView()->descriptorHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.f, 0, 0, nullptr);

    cmdList->OMSetRenderTargets(1, &mSwapChain->GetCurrentBackBufferView()->descriptorHandle, true, &mSwapChain->GetDepthStencilView()->descriptorHandle);

    ID3D12DescriptorHeap* descriptorHeaps[] = { mCbvSrvUavDescriptorHeap->gpuDescriptorHeap.Get() };
    cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

    ImGui_ImplDX12_RenderDrawData(static_cast<ImDrawData*>(data), cmdList.Get());
    cmdList->ResourceBarrier(1, &afterBarrier);

    ExecuteCmdBuffer(cmdBuffer);
    ReleaseCmdBuffer(cmdBuffer);
}

void D3DContext::CreateSceneBuffer(VisualBuffer* buffer)
{
    TextureDescriptor colorDescriptor;
    {
        colorDescriptor.width = buffer->width;
        colorDescriptor.height = buffer->height;
        colorDescriptor.slices = 1;
        colorDescriptor.sparse = false;
        colorDescriptor.mipLevel = 1;
        colorDescriptor.anisoLevel = 1;
        colorDescriptor.sample = EMSAASample::None;
        colorDescriptor.usageType = EUsageType::RenderTarget;
        colorDescriptor.textureType = ETextureType::Tex2D;
        colorDescriptor.storageType = EStorageType::Default;
        colorDescriptor.format = EGraphicsFormat::R8G8B8A8_UNorm;
        colorDescriptor.initState = ETextureInitState::PixelShaderResource;
    }
    TextureDescriptor depthStencilDesc = colorDescriptor;
    {
        depthStencilDesc.usageType = EUsageType::DepthStencil;
        depthStencilDesc.format = EGraphicsFormat::D24_S8_UNorm;
        depthStencilDesc.initState = ETextureInitState::DepthWrite;
    }
    mSceneRT = std::make_unique<D3DDepthRenderTarget>(mDevice.get(), mCbvSrvUavDescriptorHeap.get(), mRtvDescriptorHeap.get(), mDsvDescriptorHeap.get(), colorDescriptor, depthStencilDesc);
    buffer->srvHandle = mSceneRT->colorBuffer->srvView->gpuDescriptorHandleGPU.ptr;
}

void D3DContext::CreatePlainTexture(Texture& texture)
{
    if (mTextures.find(texture.name) != mTextures.end()) return;

    auto cmdBuffer = static_cast<D3DCommandBuffer*>(RequestCmdBuffer(EContextType::Graphics, "CreatePlainTexture"));
    auto cmdList = cmdBuffer->commandList;

    TextureDescriptor texDescriptor;
    {
        texDescriptor.width = texture.width;
        texDescriptor.height = texture.height;
        texDescriptor.slices = 1;
        texDescriptor.sparse = false;
        texDescriptor.mipLevel = 1;
        texDescriptor.anisoLevel = 1;
        texDescriptor.sample = EMSAASample::None;
        texDescriptor.usageType = EUsageType::Default;
        texDescriptor.textureType = ETextureType::Tex2D;
        texDescriptor.storageType = EStorageType((uint32_t)EStorageType::Default | (uint32_t)EStorageType::Static);
        texDescriptor.format = EGraphicsFormat::R8G8B8A8_UNorm;
        texDescriptor.initState = ETextureInitState::CopyDest;
    }
    auto tex = std::make_unique<D3DPlainTexture>(mDevice.get(), mCbvSrvUavDescriptorHeap.get(), texDescriptor);

    // Copy data from upload buffer to default buffer
    {
        D3D12_SUBRESOURCE_DATA texData = {};
        texData.pData = texture.data;
        texData.RowPitch = texture.width * 4;   // RGBA
        texData.SlicePitch = texture.height * texData.RowPitch;
        UpdateSubresources(cmdList.Get(), tex->resource->defaultResource.Get(), tex->resource->uploadResource.Get(), 0, 0, 1, &texData);
    }

    // Change texture state to pixel shader resource
    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(tex->resource->defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    cmdList->ResourceBarrier(1, &barrier);

    mTextures[texture.name] = std::move(tex);

    ExecuteCmdBuffer(cmdBuffer);
    ReleaseCmdBuffer(cmdBuffer);
}

void D3DContext::CreateGeometry(const Mesh& mesh)
{
    if (mMeshes.find(mesh.name) != mMeshes.end()) return;

    auto cmdBuffer = static_cast<D3DCommandBuffer*>(RequestCmdBuffer(EContextType::Graphics, "CreateGeo"));
    auto cmdList = cmdBuffer->commandList;

    auto geometry = std::make_unique<D3DMeshGeometry>();
    geometry->name = mesh.name;

    const UINT vbByteSize = (UINT)mesh.vertices.size() * sizeof(Vertex);
    const UINT ibByteSize = (UINT)mesh.indices.size() * sizeof(std::uint32_t);

    geometry->vertexByteStride = sizeof(Vertex);
    geometry->vertexBufferByteSize = vbByteSize;
    geometry->indexFormat = DXGI_FORMAT_R32_UINT;
    geometry->indexBufferByteSize = ibByteSize;
    geometry->indexCount = mesh.indices.size();

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &geometry->vertexBufferCPU));
    CopyMemory(geometry->vertexBufferCPU->GetBufferPointer(), mesh.vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &geometry->indexBufferCPU));
    CopyMemory(geometry->indexBufferCPU->GetBufferPointer(), mesh.indices.data(), ibByteSize);

    // Create resource buffer
    BufferDescriptor desc;
    {
        desc.name = mesh.name;
        desc.count = (UINT)mesh.vertices.size();
        desc.stride = sizeof(Vertex);
        desc.usageType = EUsageType::Default;
        desc.bufferType = EBufferType::Vertex;
        desc.storageType = EStorageType((uint32_t)EStorageType::Static | (uint32_t)EStorageType::Default);
        desc.initState = EBufferInitState::CopyDest;
    };
    geometry->vertexBufferGPU = std::make_unique<D3DBuffer>(mDevice.get(), desc);
    {
        desc.count = (UINT)mesh.indices.size();
        desc.stride = sizeof(uint32_t);
        desc.bufferType = EBufferType::Index;
    }
    geometry->indexBufferGPU = std::make_unique<D3DBuffer>(mDevice.get(), desc);

    // Copy data from upload buffer to default buffer
    {   // Vertex
        D3D12_SUBRESOURCE_DATA subResourceData = {};
        subResourceData.pData = mesh.vertices.data();
        subResourceData.RowPitch = vbByteSize;
        subResourceData.SlicePitch = subResourceData.RowPitch;

        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->vertexBufferGPU->resource->defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);

        UpdateSubresources(cmdList.Get(), geometry->vertexBufferGPU->resource->defaultResource.Get(), geometry->vertexBufferGPU->resource->uploadResource.Get(), 0, 0, 1, &subResourceData);
        cmdList->ResourceBarrier(1, &barrier);
    }
    {   // Index
        D3D12_SUBRESOURCE_DATA subResourceData = {};
        subResourceData.pData = mesh.indices.data();
        subResourceData.RowPitch = ibByteSize;
        subResourceData.SlicePitch = subResourceData.RowPitch;

        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->indexBufferGPU->resource->defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);

        UpdateSubresources(cmdList.Get(), geometry->indexBufferGPU->resource->defaultResource.Get(), geometry->indexBufferGPU->resource->uploadResource.Get(), 0, 0, 1, &subResourceData);
        cmdList->ResourceBarrier(1, &barrier);
    }

    mMeshes[mesh.name] = std::move(geometry);

    ExecuteCmdBuffer(cmdBuffer);
    ReleaseCmdBuffer(cmdBuffer);
}

void D3DContext::CreateShaderlab(const ShaderLab& shaderlab)
{
    Texture tex;
    auto baseTexture = std::get<std::string>(shaderlab.properties.at("_MainTex").value);
    TextureLoader::LoadTexture(&tex, baseTexture);
    tex.name = "boxBaseColor";
    CreatePlainTexture(tex);

    for (auto kernel : shaderlab.category.kernels)
    {
        auto shader = std::make_unique<D3DShader>(kernel.hlsl);
        auto pso = std::make_unique<D3DPipelineState>(mDevice.get(), kernel.tags.at("Name"), &kernel, shader.get());
        mShaders[kernel.tags.at("Name")] = std::move(shader);
        mPSOs[kernel.tags.at("Name")] = std::move(pso);
    }
}

void D3DContext::CreateRenderItem(Entity& entity)
{
    auto item = std::make_unique<D3DRenderItem>();
    item->name = entity.GetName();
    item->mesh = mMeshes.at(entity.GetMeshContainer()->meshRef.name).get();
    item->objectCBIndex = mIncreRenderItemIndex++;
    mRenderItems[item->name] = std::move(item);
}

RHICommandContext* D3DContext::GetContext(const EContextType& type)
{
    // There is only graphics buffer pool now, need to be expanded
    return mGraphicsContext.get();
}