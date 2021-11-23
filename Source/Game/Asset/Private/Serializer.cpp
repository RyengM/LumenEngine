#include "Game/Asset/Public/Serializer.h"
#include "Test/SerializeTest/Public/Derived.h"
#include <regex>

using namespace Lumen::Game;
using namespace Lumen::Core;

bool IsBadReadPtr(void* p)
{
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	if (::VirtualQuery(p, &mbi, sizeof(mbi)))
	{
		DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
		bool b = !(mbi.Protect & mask);
		// check the page is not a guard page
		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;

		return b;
	}
	return true;
}

Serializer& Serializer::GetInstance()
{
	static Serializer instance;
	return instance;
}

void Serializer::Serialize(BaseObject* obj, std::string_view path)
{
	Archive ar;
	type t = obj->get_type();
	// Support reflection
	if (t.is_valid())
		SerializeInternal(ar, obj);
	else
		ar << obj;

	std::string json = ar.GetData();
	puts(json.c_str());
}

void Serializer::SerializeInternal(Archive& ar, BaseObject* obj)
{
	ar.BeginObject();
	type t = obj->get_type();
	for (auto& p : t.get_properties(filter_item::instance_item | filter_item::non_public_access | filter_item::public_access))
	{
		if (p.get_metadata("serialize").is_valid() && p.get_metadata("serialize").to_bool())
			PutLineByDataType(ar, p, obj);
	}
	ar.EndObject();
}

void Serializer::PutLineByDataType(Archive& ar, const rttr::property& p, BaseObject* obj)
{
	auto propertyType = p.get_type();
	std::string typeName = propertyType.get_name().to_string();
	auto propertyName = p.get_name().to_string();

	if (!propertyType.is_valid())
	{
		LOG_WARN("class member name [" + propertyName + "] cannot be serialized");
		return;
	}

	if (typeName == "int")
	{
		ar << propertyName << p.get_value(obj).to_int32();
		return;
	}
	if (typeName == "unsignedint")
	{
		ar << propertyName << p.get_value(obj).to_uint32();
		return;
	}
	if (typeName == "bool")
	{
		ar << propertyName << p.get_value(obj).to_bool();
		return;
	}
	if (typeName == "float" || typeName == "double")
	{
		ar << propertyName << p.get_value(obj).to_double();
		return;
	}
	// String
	if (typeName == "classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char> >")
	{
		ar << propertyName << p.get_value(obj).to_string();
		return;
	}
	// BaseObject
	if (propertyType.get_base_classes().size() &&
		propertyType.get_base_classes().begin()->get_name().to_string() == "BaseObject")
	{
		ar << p.get_name().to_string();
		SerializeInternal(ar, &p.get_value(obj).get_value<BaseObject>());
		return;
	}
	// BaseObject pointer
	if (typeName.back() == '*')
	{
		Entity* pointer = p.get_value(obj).get_value<Entity*>();
		if (pointer == nullptr || IsBadReadPtr(pointer)) return;
		ar << p.get_name().to_string();
		SerializeInternal(ar, pointer);
		return;
	}
	// BaseObject Vector
	if (typeName.substr(0, 16) == "classstd::vector")
	{
		// Check type of content, if is not inherited from BaseObject, return
		std::string fullTypeName = p.get_type().get_name().to_string();
		std::smatch matchedTypeName;
		std::regex_search(fullTypeName, matchedTypeName, std::regex("(?!.*(:|<))([^>])*"));
		std::string typeName = matchedTypeName.str();
		typeName.pop_back();
		type t = type::get_by_name(typeName);
		if (!t.is_valid()) return;
		if (t.get_base_classes().size() && t.get_base_classes().begin()->get_name().to_string() != "BaseObject") return;

		auto vec = p.get_value(obj).get_value<std::vector<BaseObject*>>();
		ar << p.get_name().to_string();
		ar.BeginArray();
		for (auto& v : vec)
			SerializeInternal(ar, v);
		ar.EndArray();
		return;
	}
	// Other type, it is reflected, but has member which is not reflected
	{
		ar << p.get_name().to_string();
		p.get_value(obj).get_value<BaseObject>().Serialize(ar);
	}
}