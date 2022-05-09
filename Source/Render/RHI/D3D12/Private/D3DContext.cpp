#include "Game/Asset/Public/AssetManager.h"
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

void D3DContext::UpdateObjectCB(const Entity& entity)
{
    auto objectCB = mGraphicsContext->currentFrameResource->objectBuffers.get();

    ObjectConstants constants;

    Vec3 rotate = entity.GetTransform().rotation;
    Quaternion quat(rotate.Length(), rotate.Normalize());

    Mat4 world = Mat4(1.f).Scale(entity.GetTransform().scale);
    world = quat.ToRotateMatrix() * world;
    world = world.Translate(entity.GetTransform().position);

    DirectX::XMMATRIX model = MathHelper::ConvertToDxMatrix(world);
    XMStoreFloat4x4(&constants.model, model);

    if (mAllRenderItems.find(entity.GetGuid().str()) == mAllRenderItems.end()) return;
    auto item = mAllRenderItems[entity.GetGuid().str()].get();
    item->world = constants.model;
    objectCB->SetData<ObjectConstants>(item->objectCBIndex, constants, true);
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

void D3DContext::UpdateMaterialCB(const Material& mat)
{
    if (mMaterials.find(mat.guid.data()) == mMaterials.end()) return;

    auto materialCB = mGraphicsContext->currentFrameResource->materialBuffers.get();
    D3DMaterial* material = mMaterials.at(mat.guid.data()).get();
    // Update texture bind, now only support _MainTex diffuse
    for (auto& iter : mat.propertyList.texMap)
        if (mTextures.find(iter.second.guid) != mTextures.end())
            material->diffuseSrvHandle = mTextures.at(iter.second.guid)->srvView->gpuDescriptorHandleGPU;

    UINT offset = material->matCBOffset;
    materialCB->SetUnfixedBufferData(offset, mat.buffer, mat.propertyListSize);
}

void D3DContext::RenderScene(uint32_t width, uint32_t height)
{
    CD3DX12_RESOURCE_BARRIER beforeBarrier = CD3DX12_RESOURCE_BARRIER::Transition(mSceneRT->colorBuffer->resource->defaultResource.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);
    CD3DX12_RESOURCE_BARRIER afterBarrier = CD3DX12_RESOURCE_BARRIER::Transition(mSceneRT->colorBuffer->resource->defaultResource.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

    auto cmdBuffer = static_cast<D3DCommandBuffer*>(RequestCmdBuffer(EContextType::Graphics, "RenderScene"));
    auto cmdList = cmdBuffer->commandList;

    auto pso = mPSOs.at("Default").get();
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

    // Draw entities
    cmdList->SetGraphicsRootSignature(pso->rootSignature.Get());
    cmdList->SetGraphicsRootConstantBufferView(1, frameResource->passBuffers->uploadResource->GetGPUVirtualAddress());
    DrawRenderItems(cmdList.Get(), mRenderItems[(uint32_t)ERenderLayer::Opaque]);

    // Draw sky
    cmdList->SetPipelineState(mPSOs.at("SimpleSky")->d3dPso.Get());
    DrawRenderItems(cmdList.Get(), mRenderItems[(uint32_t)ERenderLayer::Sky]);

    cmdList->ResourceBarrier(1, &afterBarrier);

    ExecuteCmdBuffer(cmdBuffer);
    ReleaseCmdBuffer(cmdBuffer);
}

void D3DContext::DrawRenderItems(ID3D12GraphicsCommandList* cmdList,const  std::vector<D3DRenderItem*>& renderItems)
{
    for (auto& item : renderItems)
    {
        auto geo = item->mesh;
        if (!geo) continue;

        auto vBufferView = geo->VertexBufferView();
        auto iBufferView = geo->IndexBufferView();
        cmdList->IASetVertexBuffers(0, 1, &vBufferView);
        cmdList->IASetIndexBuffer(&iBufferView);
        cmdList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        D3D12_GPU_VIRTUAL_ADDRESS objectCBAddress = mGraphicsContext->currentFrameResource->objectBuffers->uploadResource->GetGPUVirtualAddress();
        cmdList->SetGraphicsRootConstantBufferView(0, objectCBAddress + item->objectCBIndex * ((sizeof(ObjectConstants) + 255) & ~255));
        if (item->guid != "skybox" && item->material)
            cmdList->SetGraphicsRootConstantBufferView(2, mGraphicsContext->currentFrameResource->materialBuffers->uploadResource->GetGPUVirtualAddress() + item->material->matCBOffset);
        cmdList->SetGraphicsRootDescriptorTable(3, mTextures.at("skyBox")->srvView->gpuDescriptorHandleGPU);
        if (item->material && item->material->diffuseSrvHandle.ptr)
            cmdList->SetGraphicsRootDescriptorTable(4, item->material->diffuseSrvHandle);
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

void D3DContext::CreateEntity(const Entity& entity)
{
    MeshComponent meshComponent = entity.GetMeshContainer();
    Mesh* mesh = AssetManager::GetInstance().GetMeshByGUID(xg::Guid(meshComponent.mesh.guid));
    if (mesh) CreateGeometry(mesh, meshComponent.mesh.guid);

    MeshRendererComponent meshRenderer = entity.GetMeshRenderer();
    Material* mat = AssetManager::GetInstance().GetMaterialByGUID(xg::Guid(meshRenderer.material.guid));
    if (mat)
    {
        // Only consider 2d plain texture now
        for (auto& texIter : mat->propertyList.texMap)
        {
            Texture* tex = AssetManager::GetInstance().GetTextureByGUID(xg::Guid(texIter.second.guid));
            if (tex) CreatePlainTexture(tex, texIter.second.guid);
        }
        CreateMaterial(mat, meshRenderer.material.guid);
        ShaderLab* shaderlab = AssetManager::GetInstance().GetShaderlabByGUID(xg::Guid(mat->shaderlab.guid));
        if (shaderlab) CreateShaderlab(*shaderlab);
    }
    CreateRenderItem(entity);
}

void D3DContext::UpdateEntity(const Entity& entity)
{
    MeshComponent meshComponent = entity.GetMeshContainer();
    Mesh* mesh = AssetManager::GetInstance().GetMeshByGUID(xg::Guid(meshComponent.mesh.guid));
    if (mesh) CreateGeometry(mesh, meshComponent.mesh.guid);

    MeshRendererComponent meshRenderer = entity.GetMeshRenderer();
    Material* mat = AssetManager::GetInstance().GetMaterialByGUID(xg::Guid(meshRenderer.material.guid));
    // Try to create every resource of material, create operation will return immediately if resource is existed
    if (mat)
    {
        // Only consider 2d plain texture now
        for (auto& texGuid : mat->propertyList.texMap)
        {
            Texture* tex = AssetManager::GetInstance().GetTextureByGUID(xg::Guid(texGuid.second.guid));
            if (tex) CreatePlainTexture(tex, texGuid.second.guid);
        }
        CreateMaterial(mat, meshRenderer.material.guid);
        ShaderLab* shaderlab = AssetManager::GetInstance().GetShaderlabByGUID(xg::Guid(mat->shaderlab.guid));
        if (shaderlab) CreateShaderlab(*shaderlab);
    }

    UpdateRenderItem(entity);
}

void D3DContext::CreatePlainTexture(Texture* texture, std::string_view guid)
{
    if (mTextures.find(guid.data()) != mTextures.end()) return;

    auto cmdBuffer = static_cast<D3DCommandBuffer*>(RequestCmdBuffer(EContextType::Graphics, "CreatePlainTexture"));
    auto cmdList = cmdBuffer->commandList;

    TextureDescriptor texDescriptor;
    {
        texDescriptor.width = texture->width;
        texDescriptor.height = texture->height;
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
        texData.pData = texture->data;
        texData.RowPitch = texture->width * 4;
        texData.SlicePitch = texture->height * texData.RowPitch;
        UpdateSubresources(cmdList.Get(), tex->resource->defaultResource.Get(), tex->resource->uploadResource.Get(), 0, 0, 1, &texData);
    }

    // Change texture state to pixel shader resource
    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(tex->resource->defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    cmdList->ResourceBarrier(1, &barrier);

    mTextures[guid.data()] = std::move(tex);

    ExecuteCmdBuffer(cmdBuffer);
    ReleaseCmdBuffer(cmdBuffer);
}

void D3DContext::CreateCubeMap(std::vector<Texture>& textures)
{
    auto cmdBuffer = static_cast<D3DCommandBuffer*>(RequestCmdBuffer(EContextType::Graphics, "CreateCubemap"));
    auto cmdList = cmdBuffer->commandList;

    TextureDescriptor texDescriptor;
    {
        texDescriptor.width = textures[0].width;
        texDescriptor.height = textures[0].height;
        texDescriptor.slices = 6;
        texDescriptor.sparse = false;
        texDescriptor.mipLevel = 1;
        texDescriptor.anisoLevel = 1;
        texDescriptor.sample = EMSAASample::None;
        texDescriptor.usageType = EUsageType::Default;
        texDescriptor.textureType = ETextureType::TexCube;
        texDescriptor.storageType = EStorageType((uint32_t)EStorageType::Default | (uint32_t)EStorageType::Static);
        texDescriptor.format = EGraphicsFormat::R8G8B8A8_UNorm;
        texDescriptor.initState = ETextureInitState::CopyDest;
    }
    auto cubemap = std::make_unique<D3DPlainTexture>(mDevice.get(), mCbvSrvUavDescriptorHeap.get(), texDescriptor);

    // Copy data from upload buffer to default buffer
    std::vector<D3D12_SUBRESOURCE_DATA> texDatas;
    for (int i = 0; i < 6; i++)
    {
        D3D12_SUBRESOURCE_DATA texData = {};
        texData.pData = textures[i].data;
        texData.RowPitch = textures[i].width * 4;
        texData.SlicePitch = textures[i].height * texData.RowPitch;
        texDatas.emplace_back(texData);
    }
    UpdateSubresources(cmdList.Get(), cubemap->resource->defaultResource.Get(), cubemap->resource->uploadResource.Get(), 0, 0, texDatas.size(), texDatas.data());

    // Change texture state to pixel shader resource
    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(cubemap->resource->defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    cmdList->ResourceBarrier(1, &barrier);

    mTextures["skyBox"] = std::move(cubemap);

    ExecuteCmdBuffer(cmdBuffer);
    ReleaseCmdBuffer(cmdBuffer);
}

void D3DContext::CreateGeometry(const Mesh& mesh, std::string_view guid)
{
    CreateGeometry(const_cast<Mesh*>(&mesh), guid);
}

void D3DContext::CreateGeometry(Mesh* mesh, std::string_view guid)
{
    if (mMeshes.find(guid.data()) != mMeshes.end()) return;

    auto cmdBuffer = static_cast<D3DCommandBuffer*>(RequestCmdBuffer(EContextType::Graphics, "CreateGeo"));
    auto cmdList = cmdBuffer->commandList;

    auto geometry = std::make_unique<D3DMeshGeometry>();
    geometry->name = mesh->name;

    const UINT vbByteSize = (UINT)mesh->vertices.size() * sizeof(Vertex);
    const UINT ibByteSize = (UINT)mesh->indices.size() * sizeof(std::uint32_t);

    geometry->vertexByteStride = sizeof(Vertex);
    geometry->vertexBufferByteSize = vbByteSize;
    geometry->indexFormat = DXGI_FORMAT_R32_UINT;
    geometry->indexBufferByteSize = ibByteSize;
    geometry->indexCount = mesh->indices.size();

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &geometry->vertexBufferCPU));
    CopyMemory(geometry->vertexBufferCPU->GetBufferPointer(), mesh->vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &geometry->indexBufferCPU));
    CopyMemory(geometry->indexBufferCPU->GetBufferPointer(), mesh->indices.data(), ibByteSize);

    // Create resource buffer
    BufferDescriptor desc;
    {
        desc.name = mesh->name;
        desc.count = (UINT)mesh->vertices.size();
        desc.stride = sizeof(Vertex);
        desc.usageType = EUsageType::Default;
        desc.bufferType = EBufferType::Vertex;
        desc.storageType = EStorageType((uint32_t)EStorageType::Static | (uint32_t)EStorageType::Default);
        desc.initState = EBufferInitState::CopyDest;
    };
    geometry->vertexBufferGPU = std::make_unique<D3DBuffer>(mDevice.get(), desc);
    {
        desc.count = (UINT)mesh->indices.size();
        desc.stride = sizeof(uint32_t);
        desc.bufferType = EBufferType::Index;
    }
    geometry->indexBufferGPU = std::make_unique<D3DBuffer>(mDevice.get(), desc);

    // Copy data from upload buffer to default buffer
    {   // Vertex
        D3D12_SUBRESOURCE_DATA subResourceData = {};
        subResourceData.pData = mesh->vertices.data();
        subResourceData.RowPitch = vbByteSize;
        subResourceData.SlicePitch = subResourceData.RowPitch;

        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->vertexBufferGPU->resource->defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);

        UpdateSubresources(cmdList.Get(), geometry->vertexBufferGPU->resource->defaultResource.Get(), geometry->vertexBufferGPU->resource->uploadResource.Get(), 0, 0, 1, &subResourceData);
        cmdList->ResourceBarrier(1, &barrier);
    }
    {   // Index
        D3D12_SUBRESOURCE_DATA subResourceData = {};
        subResourceData.pData = mesh->indices.data();
        subResourceData.RowPitch = ibByteSize;
        subResourceData.SlicePitch = subResourceData.RowPitch;

        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(geometry->indexBufferGPU->resource->defaultResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);

        UpdateSubresources(cmdList.Get(), geometry->indexBufferGPU->resource->defaultResource.Get(), geometry->indexBufferGPU->resource->uploadResource.Get(), 0, 0, 1, &subResourceData);
        cmdList->ResourceBarrier(1, &barrier);
    }

    mMeshes[guid.data()] = std::move(geometry);

    ExecuteCmdBuffer(cmdBuffer);
    ReleaseCmdBuffer(cmdBuffer);
}

uint32_t D3DContext::CreateMaterial(Material* mat, std::string_view guid)
{
    if (mMaterials.find(guid.data()) != mMaterials.end()) return mMaterials.at(guid.data())->matCBOffset;

    // Get material constant buffer offset, the buffer contains all material data except textures
    auto material = std::make_unique<D3DMaterial>();
    material->matCBOffset = mIncreMaterialOffset;
    // Bind textures, now only support main diffuse texture
    for (auto& iter : mat->propertyList.texMap)
    {
        if (mTextures.find(iter.second.guid) != mTextures.end())
            material->diffuseSrvHandle = mTextures.at(iter.second.guid)->srvView->gpuDescriptorHandleGPU;
    }
    mMaterials[guid.data()] = std::move(material);
    mIncreMaterialOffset += mat->propertyListSize;

    return mMaterials[guid.data()]->matCBOffset;
}

void D3DContext::CreateShaderlab(const ShaderLab& shaderlab)
{
    if (mShaders.find(shaderlab.name) != mShaders.end()) return;

    for (auto kernel : shaderlab.category.kernels)
    {
        auto shader = std::make_unique<D3DShader>(kernel.hlsl);
        auto pso = std::make_unique<D3DPipelineState>(mDevice.get(), kernel.tags.at("Name"), &kernel, shader.get());
        mShaders[kernel.tags.at("Name")] = std::move(shader);
        mPSOs[kernel.tags.at("Name")] = std::move(pso);
    }
}

void D3DContext::CreateRenderItem(const Entity& entity)
{
    auto item = std::make_unique<D3DRenderItem>();

    auto meshGuid = entity.GetMeshContainer().mesh.guid;
    if (mMeshes.find(meshGuid) != mMeshes.end())
        item->mesh = mMeshes.at(meshGuid).get();

    auto matGuid = entity.GetMeshRenderer().material.guid;
    if (mMaterials.find(matGuid) != mMaterials.end())
        item->material = mMaterials.at(matGuid).get();

    item->objectCBIndex = mIncreRenderItemIndex++;
    item->guid = entity.GetGuid().str();

    mRenderItems[(uint32_t)ERenderLayer::Opaque].push_back(item.get());
    mAllRenderItems[item->guid] = std::move(item);
}

void D3DContext::UpdateRenderItem(const Entity& entity)
{
    auto guid = entity.GetGuid().str();
    if (mAllRenderItems.find(guid) == mAllRenderItems.end()) return;

    auto item = mAllRenderItems.at(guid).get();
    auto meshGuid = entity.GetMeshContainer().mesh.guid;
    if (mMeshes.find(meshGuid) != mMeshes.end())
        item->mesh = mMeshes.at(meshGuid).get();
    auto matGuid = entity.GetMeshRenderer().material.guid;
    if (mMaterials.find(matGuid) != mMaterials.end())
        item->material = mMaterials.at(matGuid).get();
}

void D3DContext::RemoveRenderItem(std::string_view guid)
{
    // TODO. erase is slow, replace with a more effective way later
    for (int i = 0; i < mRenderItems[(uint32_t)ERenderLayer::Opaque].size(); i++)
        if (mRenderItems[(uint32_t)ERenderLayer::Opaque][i]->guid == guid.data())
            mRenderItems[(uint32_t)ERenderLayer::Opaque].erase(mRenderItems[(uint32_t)ERenderLayer::Opaque].begin() + i);
    mAllRenderItems.erase(guid.data());
}

void D3DContext::CreateSkyItem()
{
    // Hard code now, may can precompile shaderlab to support more flexible parameter binding later
    std::vector<Texture> textures;
    // Right
    textures.emplace_back(*AssetManager::GetInstance().GetTextureByGUID(xg::Guid("edb6126b-2dcb-4bca-9feb-e5b8fcb13e7a")));
    // Left
    textures.emplace_back(*AssetManager::GetInstance().GetTextureByGUID(xg::Guid("8bf66627-d9e8-4796-bcce-4e9aa086b7e5")));
    // Top
    textures.emplace_back(*AssetManager::GetInstance().GetTextureByGUID(xg::Guid("bc7da57a-cd37-4654-81a6-c9fa8fbabbf2")));
    // Bottom
    textures.emplace_back(*AssetManager::GetInstance().GetTextureByGUID(xg::Guid("60111c87-e1af-462b-b3dd-0284a6f27998")));
    // Front
    textures.emplace_back(*AssetManager::GetInstance().GetTextureByGUID(xg::Guid("2f460232-0bad-45ce-ac41-bb34b280692b")));
    // Back
    textures.emplace_back(*AssetManager::GetInstance().GetTextureByGUID(xg::Guid("89999e83-d4c2-436e-8084-2aa3b1644cca")));
    CreateCubeMap(textures);

    auto skyItem = std::make_unique<D3DRenderItem>();
    skyItem->guid = "skybox";
    skyItem->mesh = mMeshes.at("sphere-builtin").get();
    skyItem->objectCBIndex = mIncreRenderItemIndex++;
    mRenderItems[(uint32_t)ERenderLayer::Sky].push_back(skyItem.get());
    mAllRenderItems[skyItem->guid] = std::move(skyItem);
}

RHICommandContext* D3DContext::GetContext(const EContextType& type)
{
    // There is only graphics buffer pool now, need to be expanded
    return mGraphicsContext.get();
}