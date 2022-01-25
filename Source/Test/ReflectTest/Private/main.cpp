#include "Test/ReflectTest/Public/Derived.h"
#include <iostream>

using namespace Lumen::Core;
using namespace Lumen::Test;

int main() {
    type derivedType = type::get_by_name("Derived");
    variant derived = derivedType.create();
    Derived* d = derived.get_value<Derived*>();

    std::vector<BaseObject*> vec;
    vec.emplace_back(d);

    constructor cons = derivedType.get_constructor();
    constructor cons2 = derivedType.get_constructor({ type::get<int>() });
    cons.invoke();
    cons2.invoke({ 2 });

    method func = derivedType.get_method("F0", {});
    method func1 = derivedType.get_method("F0", { type::get<int>() });
    method func2 = derivedType.get_method("F0", { type::get<float>() });
    func.invoke(d);
    func1.invoke(d, 1);
    func2.invoke(d, 1.f);

    return 0;
}

