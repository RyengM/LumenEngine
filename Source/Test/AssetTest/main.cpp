#include "Game/Asset/Public/AssetManager.h"
#include <iostream>

using namespace Lumen::Game;

int main()
{
    AssetManager::GetInstance().LoadAsset("./Test.jpg");


    return 0;
}