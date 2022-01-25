#pragma once

#include "NamedValue.h"
#include "AttrList.h"
#include "detail/FieldTraits.h"
#include "Util.h"

namespace Ubpa::USRefl {
    template<typename Name, typename T, typename L, typename AList>
    struct Field : detail::FieldTraits<T>, NamedValue<Name, T> {
        static_assert(detail::IsInstance<AList, AttrList>::value);
        static_assert(!std::is_void_v<T>);

        AccessSpecifier level;
        AList attrs;

        constexpr Field(Name name, T value, L level = AccessSpecifier::DEFAULT, AList attrs = {})
            : NamedValue<Name, T>{ name, value }, level(level), attrs{ attrs }{}
    };

    template<typename Name, typename T, typename L>
    Field(Name, T, L)->Field<Name, T, L, AttrList<>>;
}
