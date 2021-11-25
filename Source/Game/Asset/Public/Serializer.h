#pragma once

#include "Core/Common/Public/BaseObject.h"
#include "ThirdParty/Rapidjson/prettywriter.h"
#include "ThirdParty/Rapidjson/document.h"

using namespace rapidjson;
using namespace Lumen::Core;

// Refer to rttr-example-json_serialization

namespace Lumen::Game
{
	// Only objects inherited from BaseObject can be serialized by this way
	// Serializer will invoke object's Serialize function and write data to a buffer recursive until meet a basic type
	// Make sure all custom types are reflected
	class Serializer
	{
	public:
		static Serializer& GetInstance();

		void Serialize(BaseObject* obj, std::string_view path);
		void SerializeInternal(PrettyWriter<StringBuffer>& writer, const rttr::instance& obj);

		void Deserialize(BaseObject* obj, std::string_view path);
		void DeserializeInternal(rttr::instance obj, Value& json);

	private:
		Serializer() {};
		~Serializer() {};
		Serializer(const Serializer&) = delete;
		Serializer& operator=(const Serializer&) = delete;

		bool WriteVariant(PrettyWriter<StringBuffer>& writer, const rttr::variant& var);
		bool WriteAtomicTypes(PrettyWriter<StringBuffer>& writer, const rttr::type& t, const rttr::variant& var);
		void WriteArray(PrettyWriter<StringBuffer>& writer, const rttr::variant_sequential_view& view);
		void WriteAssociative(PrettyWriter<StringBuffer>& writer, const rttr::variant_associative_view& view);

		rttr::variant ExtractBasicType(Value& json);
		rttr::variant ExtractValue(Value::MemberIterator& itr, const type& t);
		void ReadArray(variant_sequential_view& view, Value& value);
		void ReadAssociative(variant_associative_view& view, Value& value);
	};
}