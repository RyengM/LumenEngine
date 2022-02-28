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
        D3D12_CPU_DESCRIPTOR_HANDLE                         cpuHeapStartHandle;
        D3D12_GPU_DESCRIPTOR_HANDLE                         gpuHeapStartHandle;
        UINT                                                descriptorSize;

        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        cpuDescriptorHeap;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        gpuDescriptorHeap;
        // Avaliable space in descripter heap
        std::vector<size_t>                                 freeElements;
    };
}