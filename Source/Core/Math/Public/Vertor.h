#pragma once
#include "Core/Common/Public/BaseObject.h"

namespace Lumen::Core
{
	template <typename T>
	struct TVec2 : public BaseObject
	{
		T x, y;

		TVec2() : x(0), y(0) {};
		TVec2(T x, T y) : x(x), y(y) {};

		TVec2<T> operator+(const TVec2<T>& v) const;
		TVec2<T> operator-(const TVec2<T>& v) const;

		TVec2<T> operator*(const T num) const;
		TVec2<T> operator/(const T num) const;

		TVec2<T>& operator+=(const TVec2<T>& v);
		TVec2<T>& operator-=(const TVec2<T>& v);

		TVec2<T>& operator*=(const T num);
		TVec2<T>& operator/=(const T num);

		void Serialize(Archive& ar);

		T Dot(const TVec2<T>& v) const;

		T Length();
		TVec2<T> Normalize();
	};

	template <typename T>
	struct TVec3 : public BaseObject
	{
		T x, y, z;

		TVec3() : x(0), y(0), z(0) {};
		TVec3(T num) : x(num), y(num), z(num) {};
		TVec3(T x, T y, T z) : x(x), y(y), z(z) {};
		
		TVec3<T> operator-(void);

		TVec3<T> operator+(const TVec3<T>& v) const;
		TVec3<T> operator-(const TVec3<T>& v) const;

		TVec3<T> operator*(const T num) const;
		TVec3<T> operator/(const T num) const;

		TVec3<T>& operator+=(const TVec3<T>& v);
		TVec3<T>& operator-=(const TVec3<T>& v);

		TVec3<T>& operator*=(const T num);
		TVec3<T>& operator/=(const T num);

		bool operator==(const TVec3<T>& v) const;

		void Serialize(Archive& ar);

		T SqrLength();
		T Length();
		TVec3<T> Normalize();

		T Dot(const TVec3<T>& v) const;
		TVec3<T> Cross(const TVec3<T>& v) const;
		TVec3<T> ElementProduct(const TVec3<T>& v) const;

		TVec2<T> xy() const;
	};

	template <typename T>
	struct TVec4 : public BaseObject
	{
		T x, y, z, w;

		TVec4() : x(0), y(0), z(0), w(0) {};
		TVec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};
		TVec4(const TVec3<T>& v);
		TVec4(const TVec3<T>& v, T w);
		TVec4(const TVec2<T>& v, T z, T w);

		TVec4<T> operator+(const TVec4<T>& v) const;
		TVec4<T> operator-(const TVec4<T>& v) const;

		TVec4<T> operator*(const T num) const;
		TVec4<T> operator/(const T num) const;

		TVec4<T>& operator+=(const TVec4<T>& v);
		TVec4<T>& operator-=(const TVec4<T>& v);

		TVec4<T>& operator*=(const T num);
		TVec4<T>& operator/=(const T num);

		void Serialize(Archive& ar);

		TVec3<T> xyz() const;
		TVec2<T> xy() const;
	};

	typedef TVec2<float> Vec2;
	typedef TVec2<double> Vec2d;
	typedef TVec3<float> Vec3;
	typedef TVec3<double> Vec3d;
	typedef TVec4<float> Vec4;
	typedef TVec4<double> Vec4d;
}

#include "Details/Vertor.inl"