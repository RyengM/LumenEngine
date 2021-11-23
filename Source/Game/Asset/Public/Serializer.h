#pragma once

#include "Core/Common/Public/BaseObject.h"
#include "ThirdParty/Rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace Lumen::Core;

namespace Lumen::Game
{
	// Only objects inherited from BaseObject can be serialized by this way
	class Serializer
	{
	public:
		static Serializer& GetInstance();

		void Serialize(BaseObject* obj, std::string_view path);
		void SerializeInternal(Archive& ar, BaseObject* obj);
		void PutLineByDataType(Archive& ar, const rttr::property& p, BaseObject* obj);

	private:
		Serializer() {};
		~Serializer() {};
		Serializer(const Serializer&) = delete;
		Serializer& operator=(const Serializer&) = delete;
	};
}