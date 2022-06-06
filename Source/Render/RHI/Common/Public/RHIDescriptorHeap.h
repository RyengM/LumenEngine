#pragma once
#include <stdint.h>

namespace Lumen::Render
{
    enum class EHeapDescriptorType : uint32_t
    {
        CBV_SRV_UAV = 0,
        SAMPLER     = 1,
        RTV         = 2,
        DSV         = 3
    };

    class RHIDescriptorHeap
    {

    };
}