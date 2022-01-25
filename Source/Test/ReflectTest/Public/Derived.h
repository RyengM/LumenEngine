#pragma once

#include "Core/Common/Public/BaseObject.h"

using namespace Lumen::Core;

namespace Lumen::Test
{
    class Derived : public BaseObject
    {
    public:
        Derived();
        Derived(int a);

        [[info("test")]]
        int mDerivedPub = 4;

        void F0();
        void F0(int a);
        void F0(float a);

    private:
        int mDerivedPri = 2;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(BaseObject)
    };
}