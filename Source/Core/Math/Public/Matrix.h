#pragma once
#include "Vertor.h"

namespace Lumen::Core
{
	template <typename T>
	struct TMat3
	{
		T data[3][3];

		TMat3() {};
		TMat3(const T input[9]);
		// Identity
		TMat3(T digit);
		TMat3(const Vec3& v0, const Vec3& v1, const Vec3& v2);
		
		TMat3<T> operator*(const TMat3<T>& m) const;
		TVec3<T> operator*(const TVec3<T>& v) const;

		TMat3<T> Transpose() const;

		T At(int x, int y) const;
		void SetElement(int x, int y, T value);

		void Clear();
	};

	template <typename T>
	struct TMat4
	{
		T data[4][4];

		TMat4() {};
		TMat4(const T input[16]);
		// Identity
		TMat4(T digit);

		TMat4<T> operator*(const TMat4<T>& m) const;
		TVec4<T> operator*(const TVec4<T>& v) const;
		TVec3<T> operator*(const TVec3<T>& v) const;

		TMat4<T> HomogeneousInverse() const;
		TMat4<T> Transpose() const;

		TMat4<T>& Translate(const TVec3<T>& v);
		TMat4<T>& Scale(const TVec3<T>& v);

		T At(int x, int y) const;
		void SetElement(int x, int y, T value);

		void Clear();
	};

	typedef TMat3<float> Mat3;
	typedef TMat3<double> Mat3d;
	typedef TMat4<float> Mat4;
	typedef TMat4<double> Mat4d;
}

#include "Details/Matrix.inl"