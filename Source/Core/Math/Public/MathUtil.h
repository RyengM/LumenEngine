#pragma once

#include "Quaternion.h"

namespace Lumen::Core
{
#define PI 3.1415926535

	// Vector in math is inherited from baseObject whose size the not the same as vector itself
	// Declare pure vector structure here as Float
	struct Float2
	{
		float x = 0, y = 0;
	};

	struct Float3
	{
		float x = 0, y = 0, z = 0;
	};

	struct Float4
	{
		float x = 0, y = 0, z = 0, w = 0;
	};

	class MathUtil
	{
	public:
		static float Angle2Radian(float degree);
		static double Angle2Radian(double degree);

		static float Radian2Angle(float radian);
		static double Radian2Angle(double radian);

		static float Clamp(float value, float a, float b);
		static Vec2 Clamp(const Vec2& value, float a, float b);
		static Vec3 Clamp(const Vec3& value, float a, float b);

		static float Lerp(float s0, float s1, float t);
		static Vec2 Lerp(const Vec2& s0, const Vec2& s1, float t);
		static Vec3 Lerp(const Vec3& s0, const Vec3& s1, float t);
		static Vec4 Lerp(const Vec4& s0, const Vec4& s1, float t);

		static float Abs(float v);

		static int Pow(int x, int n);
		static Vec3 Pow(Vec3 v, float gamma);

		static Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
		static Mat4 Ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane);

		static Float3 Normalize(const Float3& vec);
	};
}