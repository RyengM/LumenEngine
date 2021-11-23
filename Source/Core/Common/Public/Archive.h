#pragma once

#include "ThirdParty/Rapidjson/prettywriter.h"
#include <string>
#include <concepts>

namespace Lumen::Core
{
	class Archive
	{
		using Writer = rapidjson::PrettyWriter<rapidjson::StringBuffer>;

	public:
		Archive();

		Archive& operator<<(int v);
		Archive& operator<<(unsigned int v);
		Archive& operator<<(float v);
		Archive& operator<<(double v);
		Archive& operator<<(bool v);
		Archive& operator<<(const char* v);
		Archive& operator<<(std::string_view v);

		inline void BeginObject() noexcept { writer.StartObject(); };
		inline void EndObject() noexcept { writer.EndObject(); };
		inline void BeginArray() noexcept { writer.StartArray(); }
		inline void EndArray() noexcept { writer.EndArray(); }

		inline std::string GetData() const noexcept { return buffer.GetString(); };

	private:
		rapidjson::StringBuffer buffer;
		Writer writer;
	};
}