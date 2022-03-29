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
	data = new uint8_t[rhs.width * rhs.height * rhs.channel];
	memcpy(data, rhs.data, rhs.width * rhs.height * rhs.channel);
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
	stbi_set_flip_vertically_on_load(true);
	unsigned char* input = stbi_load(sourceFile.data(), &tex->width, &tex->height, &tex->channel, 0);

	if (!input)
	{
		stbi_image_free(input);
		return;
	}
	
	tex->data = new uint8_t[tex->width * tex->height * tex->channel];
	memcpy(tex->data, input, tex->width * tex->height * tex->channel);

	stbi_image_free(input);
}