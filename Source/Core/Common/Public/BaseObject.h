#pragma once

#include "Core/Logger/Public/Logger.h"
#include "ThirdParty/RTTR/registration.h"
#include "ThirdParty/RTTR/registration_friend.h"

using namespace rttr;

namespace Lumen::Core
{
	// Base class of all can be serialized
	// This class provide the ability of reflection and serialization auto gen
	class BaseObject
	{
	public:
		BaseObject();

		RTTR_ENABLE()
	};
}