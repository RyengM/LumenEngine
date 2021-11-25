#include "Test/SerializeTest/Public/Derived.h"
#include "Game/Asset/Public/Serializer.h"
#include <iostream>

using namespace Lumen::Game;
using namespace Lumen::Test;

int main() {
	type derivedType = type::get_by_name("Derived");
	variant derived = derivedType.create({ std::string_view("TestObject") });

	Derived* s = derived.get_value<Derived*>();
	s->mAge = 50;
	Serializer::GetInstance().Serialize(s, "./test.json");
	
	Derived d;
	Serializer::GetInstance().Deserialize(&d, "./test.json");

	return 0;
}