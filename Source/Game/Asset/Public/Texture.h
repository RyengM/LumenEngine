#pragma once

#include <string>

namespace Lumen::Game
{
    struct Texture
    {
        std::string name;

        int width;
        int height;
        int channel;

        uint8_t* data;

        ~Texture();
    };

    class TextureLoader
    {
    public:
        static void LoadTexture(Texture* tex, std::string_view sourceFile);
    };
}