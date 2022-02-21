#pragma once

#include "Render/RHI/D3D12/Public/D3DDescriptorHeap.h"

using namespace Lumen::Render;

D3D12_DESCRIPTOR_HEAP_TYPE GetD3DDescriptorHeapType(const EHeapDescriptorType type)
{
    if (type == EHeapDescriptorType::CBV_SRV_UAV)
        return D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    else if (type == EHeapDescriptorType::SAMPLER)
        return D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
    else if (type == EHeapDescriptorType::RTV)
        return D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    return D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
}

D3DDescriptorHeap::D3DDescriptorHeap(RHIDevice* rhiDevice, const EHeapDescriptorType type, size_t count)
{
    D3DDevice* device = static_cast<D3DDevice*>(rhiDevice);
    D3D12_DESCRIPTOR_HEAP_TYPE heapType = GetD3DDescriptorHeapType(type);
    descriptorSize = device->d3dDevice->GetDescriptorHandleIncrementSize(heapType);

    mFreeElements.resize(count);
    for (int i = 0; i < count; i++) mFreeElements[i] = i;

    D3D12_DESCRIPTOR_HEAP_DESC descriptorCPU;
    {
        descriptorCPU.Flags             = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        descriptorCPU.Type              = heapType;
        descriptorCPU.NumDescriptors    = count;
        descriptorCPU.NodeMask          = 0;
    }
    ThrowIfFailed(device->d3dDevice->CreateDescriptorHeap(&descriptorCPU, IID_PPV_ARGS(&mCPUDescriptorHeap)));
    cpuHeapStartHandle = mCPUDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

    if (type != EHeapDescriptorType::CBV_SRV_UAV) return;

    D3D12_DESCRIPTOR_HEAP_DESC descriptorGPU;
    {
        descriptorGPU.Flags             = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        descriptorGPU.Type              = heapType;
        descriptorGPU.NumDescriptors    = count;
        descriptorGPU.NodeMask          = 0;
    }
    ThrowIfFailed(device->d3dDevice->CreateDescriptorHeap(&descriptorGPU, IID_PPV_ARGS(&mGPUDescriptorHeap)));
    gpuHeapStartHandle = mGPUDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
}

size_t D3DDescriptorHeap::RequestElement()
{
    size_t index = mFreeElements.back();
    mFreeElements.pop_back();
    return index;
}

void D3DDescriptorHeap::ReturnElement(size_t index)
{
    mFreeElements.push_back(index);
}