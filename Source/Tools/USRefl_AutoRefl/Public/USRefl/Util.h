#pragma once

namespace Ubpa::USRefl {
    enum class AccessSpecifier {
        PUBLIC,
        PROTECTED,
        PRIVATE,
        DEFAULT
    };

    template<typename Signature>
    constexpr auto WrapConstructor();
    template<typename T>
    constexpr auto WrapDestructor();
}

#include "detail/Util.inl"
