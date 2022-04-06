#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/Stb/stb_image.h"

#include "Game/Asset/Public/Texture.h"

using namespace Lumen::Game;

Texture::Texture(const Texture& rhs)
{
	name = rhs.name;
	width = rhs.width;
	height = rhs.height;
	channel = rhs.channel;
	// Force image to 4 channel
	data = new uint8_t[rhs.width * rhs.height * STBI_rgb_alpha];
	memcpy(data, rhs.data, rhs.width * rhs.height * STBI_rgb_alpha);
}

Texture::Texture(Texture&& rhs)
{
	name = std::move(rhs.name);
	width = rhs.width;
	height = rhs.height;
	channel = rhs.channel;
	data = rhs.data;
	rhs.data = nullptr;
}

Texture::~Texture()
{
	if (data)
		delete data;
}

void TextureLoader::LoadTexture(Texture* tex, std::string_view sourceFile)
{
	unsigned char* input = stbi_load(sourceFile.data(), &tex->width, &tex->height, &tex->channel, STBI_rgb_alpha);

	if (!input)
	{
		stbi_image_free(input);
		return;
	}

	tex->data = new unsigned char[tex->width * tex->height * STBI_rgb_alpha];
	memcpy(tex->data, input, tex->width * tex->height * STBI_rgb_alpha);

	stbi_image_free(input);
}