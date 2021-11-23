#pragma once

#include "Game/GamePlay/Public/Entity.h"
#include "Game/GamePlay/Public/Component.h"
#include "Core/Math/Public/Vertor.h"

using namespace Lumen::Game;
using namespace Lumen::Core;
using namespace rttr;

namespace Lumen::Test
{
    class DerivedComponent : public Component
    {
    public:
        [[serialize(true)]]
        int mSub = 10;

        RTTR_ENABLE(Component)
    };

    class DerivedSubComponent : public DerivedComponent
    {
    public:
        DerivedSubComponent() = default;
        DerivedSubComponent(int num) : mDerivedSub(num) {}

        [[serialize(true)]]
        int mDerivedSub = 20;

        [[serialize(true)]]
        AssetRef mAssetRef;

        RTTR_ENABLE(DerivedComponent)
    };

	class Derived : public Entity
	{
    public:
        Derived() = default;
        Derived(std::string_view name);

        void Func();

        [[serialize(true)]]
        int mAge = 23;

        [[serialize(true)]]
        unsigned int mUnsignedInt = 233;

        [[serialize(true)]]
        bool mFlag = false;

        float mFloat = 10.f;

        [[serialize(true)]]
        double mDouble = 10.0;

        [[serialize(true)]]
        Vec3 mVec = Vec3(1,2,3);

        [[serialize(true)]]
        DerivedSubComponent mObj;

        [[serialize(true)]]
        std::vector<DerivedSubComponent*> mObjs;

    private:
        [[serialize(true)]]
        std::string mSecrect = "guess";

		RTTR_REGISTRATION_FRIEND
		RTTR_ENABLE(Entity)
	};
}