// Some explanation about macro used in Objects
// RTTR_REGISTRATION_FRIEND: use if the private or protected member of class should be reflected
// RTTR_ENABLE(...):		 use if the class has inheritance structure

// About Serialize
// Serializer will invoke object's Serialize function and write data to a buffer recursive until meet a basic type or 3rd party type
// For all classes without 3rd party member, serialization will be completed automatically
// For other classes with 3rd party member, override Serialize/Deserialize function mannualy

#pragma once

#include "Core/Common/Public/Archive.h"
#include "Core/Logger/Public/Logger.h"
#include "ThirdParty/RTTR/registration.h"
#include "ThirdParty/RTTR/registration_friend.h"

using namespace rttr;

namespace Lumen::Core
{
	// Base class of all class can be serialized
	// This class provide the ability of reflection and serialization auto gen
	class BaseObject
	{
	public:
		BaseObject();

		virtual void Serialize(Archive& ar) {}

		RTTR_ENABLE()
	};
}