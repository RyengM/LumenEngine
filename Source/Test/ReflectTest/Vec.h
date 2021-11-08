#pragma once

#include <tuple>

namespace Lumen::Refl {

	template<typename T>
	struct [[size(sizeof(T))]] Vec {

		REFLECTION_REGISTRATION(Lumen::Refl::Vec<T>);

		Vec() : x{ 0.f }, y{ 0.f } {}
		Vec(T x, T y) : x{ x }, y{ y } {}
		~Vec() {}

		[[not_serialize]] // non-value attr
		T x;
		[[info("hello"), maximum(10.f)]] // attr list
		T y;
		// static member variable
		inline static std::size_t num{ 0 };

		// non-static member function
		float Sum() const {
			return x + y;
		}
		// overload function, default value
		float Sum(float z, float o = 1.f) const {
			return x + y + z + o;
		}

		// static member function
		static T Dot(const Vec& lhs, const Vec& rhs) {
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

	private:
		[[info("i'm private")]]
		T z = 0;
	};
}

// Code generation tool will generate this file by code gen tool
#include "Vec_AutoRefl.inl"