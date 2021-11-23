#pragma once

#include "Game/GamePlay/Public/BaseObject.h"

using namespace Lumen::Game;
using namespace rttr;

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

		DECLARE_SERIALIZE
		RTTR_ENABLE(BaseObject)
	};
}