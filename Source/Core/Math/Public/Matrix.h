#pragma once

#include "Vector.h"

namespace Lumen::Core
{
	struct Mat3 : public BaseObject
	{
		float data[3][3] = {0};

		Mat3() {};
		Mat3(const float input[9]);
		// Identity
		Mat3(float digit);
		Mat3(const Vec3& v0, const Vec3& v1, const Vec3& v2);

		Mat3 operator*(const Mat3& m) const;
		Vec3 operator*(const Vec3& v) const;

		Mat3 Transpose() const;

		float At(int x, int y) const;
		void SetElement(int x, int y, float value);

		void Clear();

		RTTR_ENABLE(BaseObject)
	};

	struct Mat4 : public BaseObject
	{
		float data[4][4] = {0};

		Mat4() {};
		Mat4(const float input[16]);
		// Identity
		Mat4(float digit);

		Mat4 operator*(const Mat4& m) const;
		Vec4 operator*(const Vec4& v) const;
		Vec3 operator*(const Vec3& v) const;

		Mat4 HomogeneousInverse() const;
		Mat4 Transpose() const;

		Mat4& Translate(const Vec3& v);
		Mat4& Scale(const Vec3& v);

		float At(int x, int y) const;
		void SetElement(int x, int y, float value);

		void Clear();

		RTTR_ENABLE(BaseObject)
	};
}