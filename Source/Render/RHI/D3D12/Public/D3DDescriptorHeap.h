#pragma once

#include "D3DDevice.h"
#include "Render/RHI/Common/Public/RHIDescriptorHeap.h"

namespace Lumen::Render
{
    class D3DDescriptorHeap : public RHIDescriptorHeap
    {
    public:
        D3DDescriptorHeap(RHIDevice* rhiDevice, const EHeapDescriptorType type, size_t count);

        size_t RequestElement();
        void ReturnElement(size_t index);

    public:
        // Handle for cpu descriptor heap
        D3D12_CPU_DESCRIPTOR_HANDLE                         cpuHeapStartHandleCPU;
        D3D12_GPU_DESCRIPTOR_HANDLE                         gpuHeapStartHandleCPU;

        // Handle for gpu descriptor heap
        D3D12_CPU_DESCRIPTOR_HANDLE                         cpuHeapStartHandleGPU;
        D3D12_GPU_DESCRIPTOR_HANDLE                         gpuHeapStartHandleGPU;
        UINT                                                descriptorSize;

        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        cpuDescriptorHeap;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        gpuDescriptorHeap;
        // Avaliable space in descripter heap
        std::vector<size_t>                                 freeElements;
    };
}