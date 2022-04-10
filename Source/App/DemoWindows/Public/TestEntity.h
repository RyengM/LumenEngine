#pragma once

#include "Game/GamePlay/Public/Entity.h"

using namespace Lumen::Game;

class TestEntity : public Entity
{
public:
    TestEntity();

    virtual void BeginPlay() override;
    virtual void Tick() override;

private:
    [[serialize(true)]]
    int mIntValue = 0;

    [[serialize(true)]]
    std::string mStrValue = "Test";

    RTTR_REGISTRATION_FRIEND
    RTTR_ENABLE(Entity)
};