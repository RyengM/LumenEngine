#pragma once

namespace Lumen::Render
{
    class RHISwapChain
    {
    protected:
        int                                                 mCurrBackBuffer = 0;
        static const int                                    mSwapChainBufferCount = 2;
    };
}