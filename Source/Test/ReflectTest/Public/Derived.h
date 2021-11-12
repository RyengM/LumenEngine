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

        int mDerivedPub = 4;

        virtual void Test() override;

        void F0();
        void F0(int a);
        void F0(float a);

    private:
        int mDerivedPri = 2;

		RTTR_REGISTRATION_FRIEND
		RTTR_ENABLE(BaseObject)
	};
}