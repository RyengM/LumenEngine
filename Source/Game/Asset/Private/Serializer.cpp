#include "Game/Asset/Public/Serializer.h"
#include "Test/SerializeTest/Public/Derived.h"
#include <regex>
#include <fstream>

using namespace Lumen::Game;
using namespace Lumen::Core;

std::string ReadFileIntoString(std::string_view filename) {
	std::ifstream ifile(filename.data());
	if (!ifile.is_open())
	{
		LOG_ERROR("open fail : " + std::string(filename));
		return "";
	}	

	std::ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	return buf.str();
}

std::string GetFullPath(std::string_view path)
{
	std::string inputDir = path.data();
	char outDir[1024];

#ifdef _WIN32
	auto rst = _fullpath(outDir, inputDir.c_str(), 1024);
#else
	realpath(inputDir.c_str(), outDir);
#endif

	return outDir;
}

Serializer& Serializer::GetInstance()
{
	static Serializer instance;
	return instance;
}

void Serializer::Serialize(BaseObject* obj, std::string_view path)
{
	if (!obj->get_type().is_valid())
	{
		LOG_WARN("Serialized object [" + std::string(obj->get_type().get_name()) + "] is not reflected type, serialize fail");
		return;
	}

	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);

	SerializeInternal(writer, obj);

	std::string json = buffer.GetString();
	puts(json.c_str());

	// Output data to local
	auto outDir = GetFullPath(path.data());

	std::ofstream out(outDir);
	if (!out.is_open())
		LOG_ERROR("open fail : " + std::string(outDir));
	out << json;
	out.close();
}

void Serializer::SerializeInternal(PrettyWriter<StringBuffer>& writer, const rttr::instance& obj)
{
	writer.StartObject();
	type t = obj.get_derived_type();

	for (auto& p : t.get_properties(filter_item::instance_item | filter_item::non_public_access | filter_item::public_access))
	{
		if (p.get_metadata("serialize").is_valid() && p.get_metadata("serialize").to_bool())
		{
			variant var = p.get_value(obj);
			if (!var) continue;

			writer.String(p.get_name().data(), static_cast<rapidjson::SizeType>(p.get_name().length()), false);
			if (!WriteVariant(writer, var))
				LOG_WARN("cannot seralize property [" + std::string(p.get_name()) + "]");
		}
	}
	writer.EndObject();
}

void Serializer::Deserialize(BaseObject* obj, std::string_view path)
{
	rttr::instance objRef(obj);
	Document doc;
	auto json = ReadFileIntoString(GetFullPath(path));
	if (doc.Parse(json.c_str()).HasParseError())
		return;

	DeserializeInternal(objRef, doc);
}

void Serializer::DeserializeInternal(rttr::instance obj, Value& json)
{
	type t = obj.get_derived_type();
	for (auto& p : t.get_properties(filter_item::instance_item | filter_item::non_public_access | filter_item::public_access))
	{
		Value::MemberIterator ret = json.FindMember(p.get_name().data());
		if (ret == json.MemberEnd())
			continue;
		if (p.get_metadata("serialize").is_valid() && p.get_metadata("serialize").to_bool())
		{
			const auto propertyType = p.get_type();
			auto& jsonValue = ret->value;
			switch (jsonValue.GetType())
			{
			case kArrayType:
			{
				variant var;
				if (propertyType.is_sequential_container())
				{
					var = p.get_value(obj);
					auto view = var.create_sequential_view();
					ReadArray(view, jsonValue);
				}
				else if (propertyType.is_associative_container())
				{
					var = p.get_value(obj);
					auto associativeView = var.create_associative_view();
					ReadAssociative(associativeView, jsonValue);
				}

				p.set_value(obj, var);
				break;
			}
			case kObjectType:
			{
				variant var = p.get_value(obj);
				DeserializeInternal(var, jsonValue);
				p.set_value(obj, var);
				break;
			}
			default:
			{
				variant extractedValue = ExtractBasicType(jsonValue);
				if (extractedValue.convert(propertyType)) // REMARK: CONVERSION WORKS ONLY WITH "const type", check whether this is correct or not!
					p.set_value(obj, extractedValue);
			}
			}
		}
	}
}

bool Serializer::WriteVariant(PrettyWriter<StringBuffer>& writer, const rttr::variant& var)
{
	auto valueType = var.get_type();
	auto wrappedType = valueType.is_wrapper() ? valueType.get_wrapped_type() : valueType;
	bool bWrapper = wrappedType != valueType;

	// Atithmetic type
	if (WriteAtomicTypes(writer, bWrapper ? wrappedType : valueType, bWrapper ? var.extract_wrapped_value() : var)) {}
	// Array type
	else if (var.is_sequential_container())
		WriteArray(writer, var.create_sequential_view());
	// Key-value type
	else if (var.is_associative_container())
		WriteAssociative(writer, var.create_associative_view());
	// Other type
	else
	{
		auto childProps = bWrapper ? wrappedType.get_properties() : valueType.get_properties();
		// Object reflected
		if (!childProps.empty())
			SerializeInternal(writer, var);
		else
		{
			bool ok = false;
			auto text = var.to_string(&ok);
			if (!ok)
			{
				writer.String(text.c_str());
				return false;
			}

			writer.String(text.c_str());
		}
	}

	return true;
}

bool Serializer::WriteAtomicTypes(PrettyWriter<StringBuffer>& writer, const rttr::type& t, const rttr::variant& var)
{
	if (t.is_arithmetic())
	{
		if (t == type::get<bool>())
			writer.Bool(var.to_bool());
		else if (t == type::get<char>())
			writer.Bool(var.to_bool());
		else if (t == type::get<int8_t>())
			writer.Int(var.to_int8());
		else if (t == type::get<int16_t>())
			writer.Int(var.to_int16());
		else if (t == type::get<int32_t>())
			writer.Int(var.to_int32());
		else if (t == type::get<int64_t>())
			writer.Int64(var.to_int64());
		else if (t == type::get<uint8_t>())
			writer.Uint(var.to_uint8());
		else if (t == type::get<uint16_t>())
			writer.Uint(var.to_uint16());
		else if (t == type::get<uint32_t>())
			writer.Uint(var.to_uint32());
		else if (t == type::get<uint64_t>())
			writer.Uint64(var.to_uint64());
		else if (t == type::get<float>())
			writer.Double(var.to_double());
		else if (t == type::get<double>())
			writer.Double(var.to_double());

		return true;
	}
	else if (t.is_enumeration())
	{
		bool ok = false;
		auto result = var.to_string(&ok);
		if (ok)
			writer.String(var.to_string().c_str());
		else
		{
			ok = false;
			auto value = var.to_uint64(&ok);
			if (ok)
				writer.Uint64(value);
			else
				writer.Null();
		}

		return true;
	}
	else if (t == type::get<std::string>())
	{
		writer.String(var.to_string().c_str());
		return true;
	}

	return false;
}

void Serializer::WriteArray(PrettyWriter<StringBuffer>& writer, const rttr::variant_sequential_view& view)
{
	writer.StartArray();
	for (const auto& item : view)
	{
		if (item.is_sequential_container())
			WriteArray(writer, item.create_sequential_view());
		else
		{
			variant wrappedVar = item.extract_wrapped_value();
			type valueType = wrappedVar.get_type();
			if (valueType.is_arithmetic() || valueType == type::get<std::string>() || valueType.is_enumeration())
				WriteAtomicTypes(writer, valueType, wrappedVar);
			else
				SerializeInternal(writer, wrappedVar);
		}
	}
	writer.EndArray();
}

void Serializer::WriteAssociative(PrettyWriter<StringBuffer>& writer, const rttr::variant_associative_view& view)
{
	static const string_view keyName("key");
	static const string_view valueName("value");

	writer.StartArray();
	if (view.is_key_only_type())
		for (auto& item : view)
			WriteVariant(writer, item.first);
	else
	{
		for (auto& item : view)
		{
			writer.StartObject();

			writer.String(keyName.data(), static_cast<rapidjson::SizeType>(keyName.length()), false);
			WriteVariant(writer, item.first);

			writer.String(valueName.data(), static_cast<rapidjson::SizeType>(valueName.length()), false);
			WriteVariant(writer, item.second);

			writer.EndObject();
		}
	}
	writer.EndArray();
}

rttr::variant Serializer::ExtractBasicType(Value& json)
{
	switch (json.GetType())
	{
	case kStringType:
	{
		return std::string(json.GetString());
		break;
	}
	case kNullType:     break;
	case kFalseType:
	case kTrueType:
	{
		return json.GetBool();
		break;
	}
	case kNumberType:
	{
		if (json.IsInt())
			return json.GetInt();
		else if (json.IsDouble())
			return json.GetDouble();
		else if (json.IsUint())
			return json.GetUint();
		else if (json.IsInt64())
			return json.GetInt64();
		else if (json.IsUint64())
			return json.GetUint64();
		break;
	}
	// We handle only the basic types here
	case kObjectType:
	case kArrayType: return variant();
	}

	return variant();
}

rttr::variant Serializer::ExtractValue(Value::MemberIterator& itr, const type& t)
{
	auto& value = itr->value;
	variant extractedValue = ExtractBasicType(value);
	const bool bConvert = extractedValue.convert(t);
	if (!bConvert)
	{
		if (value.IsObject())
		{
			constructor ctor = t.get_constructor();
			for (auto& item : t.get_constructors())
			{
				if (item.get_instantiated_type() == t)
					ctor = item;
			}
			extractedValue = ctor.invoke();
			DeserializeInternal(extractedValue, value);
		}
	}

	return extractedValue;
}

void Serializer::ReadArray(variant_sequential_view& view, Value& value)
{
	view.set_size(value.Size());
	const type valueType = view.get_rank_type(1);

	for (SizeType i = 0; i < value.Size(); ++i)
	{
		auto& jsonIndexValue = value[i];
		if (jsonIndexValue.IsArray())
		{
			auto subArrayView = view.get_value(i).create_sequential_view();
			ReadArray(subArrayView, jsonIndexValue);
		}
		else if (jsonIndexValue.IsObject())
		{
			variant varTemp = view.get_value(i);
			variant wrappedVar = varTemp.extract_wrapped_value();
			DeserializeInternal(wrappedVar, jsonIndexValue);
			view.set_value(i, wrappedVar);
		}
		else
		{
			variant extractedValue = ExtractBasicType(jsonIndexValue);
			if (extractedValue.convert(valueType))
				view.set_value(i, extractedValue);
		}
	}
}

void Serializer::ReadAssociative(variant_associative_view& view, Value& value)
{
	for (SizeType i = 0; i < value.Size(); ++i)
	{
		auto& jsonIndexValue = value[i];
		// Key-value associative type
		if (jsonIndexValue.IsObject())
		{
			Value::MemberIterator keyItr = jsonIndexValue.FindMember("key");
			Value::MemberIterator valueItr = jsonIndexValue.FindMember("value");

			if (keyItr != jsonIndexValue.MemberEnd() &&
				valueItr != jsonIndexValue.MemberEnd())
			{
				auto keyVar = ExtractValue(keyItr, view.get_key_type());
				auto valueVar = ExtractValue(valueItr, view.get_value_type());
				if (keyVar && valueVar)
				{
					view.insert(keyVar, valueVar);
				}
			}
		}
		// Key only associative type
		else
		{
			variant extractedValue = ExtractBasicType(jsonIndexValue);
			if (extractedValue && extractedValue.convert(view.get_key_type()))
				view.insert(extractedValue);
		}
	}
}