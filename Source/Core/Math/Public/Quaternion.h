#pragma once

#include "Matrix.h"

namespace Lumen::Core
{
    struct Quaternion
    {
		float w, x, y, z;
		Vec3 v;

		Quaternion() : w(0), x(0), y(0), z(0) {}
		Quaternion(float w, float x, float y, float z);
		Quaternion(float theta, const Vec3& axis);

		Quaternion operator*(const Quaternion& q) const;
		Quaternion operator/(float num) const;

		Quaternion Conjugate();
		Quaternion Inverse();

		Mat4 ToRotateMatrix();
    };
}