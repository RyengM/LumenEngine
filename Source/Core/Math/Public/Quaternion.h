#pragma once

#include "Matrix.h"

namespace Lumen::Core
{
    struct Quaternion
    {
		float w, x, y, z = 0.f;
		Vec3 v;

		Quaternion() {}
		Quaternion(float w, float x, float y, float z);
		Quaternion(float theta, const Vec3& axis);

		Quaternion operator*(const Quaternion& q) const;
		Quaternion operator/(float num) const;

		Quaternion Conjugate();
		Quaternion Inverse();

		Mat4 ToRotateMatrix();
    };
}