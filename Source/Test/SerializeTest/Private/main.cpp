#include "Test/SerializeTest/Public/Derived.h"
#include "Game/Asset/Public/Serializer.h"
#include <iostream>

using namespace Lumen::Game;
using namespace Lumen::Test;

int main() {
	type derivedType = type::get_by_name("Derived");
	variant derived = derivedType.create({ std::string_view("TestObject") });
	Derived* d = derived.get_value<Derived*>();

	Serializer::GetInstance().Serialize(d, "./");
	
	return 0;
}