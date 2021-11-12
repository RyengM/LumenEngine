#pragma once

#include "ThirdParty/Rapidjson/rapidjson.h"

namespace Lumen::Game
{
	class Serializer
	{
	public:
		static Serializer& GetInstance();

		template<typename T>
		void Serialize(T* obj);

	private:
		Serializer() {};
		~Serializer() {};
		Serializer(const Serializer&) = delete;
		Serializer& operator=(const Serializer&) = delete;
	};
}

#include "Details/Serializer.inl"