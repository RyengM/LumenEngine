#pragma once

namespace Lumen::Game
{
    class AssetManager
    {
    public:
        static AssetManager& GetInstance();

    private:
        AssetManager();
        ~AssetManager();
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;
    };
}