#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/Stb/stb_image.h"

#include "Game/Asset/Public/Texture.h"

using namespace Lumen::Game;

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
	for (int i = 0; i < tex->width * tex->height * tex->channel; i++)
		tex->data[i] = input[i];

	stbi_image_free(input);
}