#include "Game/Asset/Public/Serializer.h"

using namespace Lumen::Game;

Serializer& Serializer::GetInstance()
{
	static Serializer instance;
	return instance;
}