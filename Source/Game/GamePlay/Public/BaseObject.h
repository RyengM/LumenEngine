#pragma once

#include "ThirdParty/RTTR/registration.h"
#include "ThirdParty/RTTR/registration_friend.h"

using namespace rttr;

namespace Lumen::Game 
{
	// Base class of all objects
	class BaseObject
	{
	public:
		virtual void Test() = 0;

		RTTR_REGISTRATION_FRIEND
		RTTR_ENABLE()
	};
}