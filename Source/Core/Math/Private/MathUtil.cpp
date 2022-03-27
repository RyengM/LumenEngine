#include "Core/Math/Public/MathUtil.h"

using namespace Lumen::Core;

float MathUtil::Angle2Radian(float degree)
{
	return degree / 180.f * PI;
}

double MathUtil::Angle2Radian(double degree)
{
	return degree / 180.0 * PI;
}

float MathUtil::Radian2Angle(float radian)
{
	return radian / PI * 180.f;
}

double MathUtil::Radian2Angle(double radian)
{
	return radian / PI * 180.0;
}

float MathUtil::Clamp(float value, float a, float b)
{
	float min = std::min(a, b);
	float max = std::max(a, b);
	return std::max(min, std::min(value, max));
}

Vec2 MathUtil::Clamp(const Vec2& value, float a, float b)
{
	float min = std::min(a, b);
	float max = std::max(a, b);
	Vec2 ret;
	ret.x = std::max(min, std::min(value.x, max));
	ret.y = std::max(min, std::min(value.y, max));
	return ret;
}

Vec3 MathUtil::Clamp(const Vec3& value, float a, float b)
{
	float min = std::min(a, b);
	float max = std::max(a, b);
	Vec3 ret;
	ret.x = std::max(min, std::min(value.x, max));
	ret.y = std::max(min, std::min(value.y, max));
	ret.z = std::max(min, std::min(value.z, max));
	return ret;
}

float MathUtil::Lerp(float s0, float s1, float t)
{
	return s0 - t * s0 + t * s1;
}

Vec2 MathUtil::Lerp(const Vec2& s0, const Vec2& s1, float t)
{
	return Vec2(s0.x - t * s0.x + t * s1.x, s0.y - t * s0.y + t * s1.y);
}

Vec3 MathUtil::Lerp(const Vec3& s0, const Vec3& s1, float t)
{
	return Vec3(s0.x - t * s0.x + t * s1.x, s0.y - t * s0.y + t * s1.y, s0.z - t * s0.z + t * s1.z);
}

Vec4 MathUtil::Lerp(const Vec4& s0, const Vec4& s1, float t)
{
	return Vec4(s0.x - t * s0.x + t * s1.x, s0.y - t * s0.y + t * s1.y, s0.z - t * s0.z + t * s1.z, s0.w - t * s0.w + t * s1.w);
}

float MathUtil::Abs(float v)
{
	return v < 0 ? -v : v;
}

int MathUtil::Pow(int x, int n)
{
	if (x == 0 || n < 0) return -1;
	if (n == 0) return 1;

	bool bPositive = true;
	if (x < 0)
	{
		x = -x;
		if (n % 2 != 0)
			bPositive = false;
	}
	int ret = 1;
	int base = x;
	while (n)
	{
		if (n % 2)
			ret *= base;
		base *= base;
		n /= 2;
	}
	return bPositive ? ret : -ret;
}

Vec3 MathUtil::Pow(Vec3 v, float gamma)
{
	Vec3 ret;
	ret.x = pow(v.x, gamma);
	ret.y = pow(v.y, gamma);
	ret.z = pow(v.z, gamma);
	return ret;
}

Mat4 MathUtil::LookAt(const Vec3& eye, const Vec3& at, const Vec3& up)
{
	Vec3 z = (at - eye).Normalize();
	Vec3 x = (up).Cross(z).Normalize();
	Vec3 y = z.Cross(x).Normalize();

	Mat4 translate(1.f);
	translate.SetElement(0, 3, -eye.x);
	translate.SetElement(1, 3, -eye.y);
	translate.SetElement(2, 3, -eye.z);

	// Base transformation
	float arrRotate[16] = { x.x, x.y, x.z, 0,
							y.x, y.y, y.z, 0,
							z.x, z.y, z.z, 0,
							0, 0, 0, 1 };
	Mat4 rotate(arrRotate);

	return rotate * translate;
}

Mat4 MathUtil::Ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	float arrOrthoTranslate[16] = { 1, 0, 0, -(left + right) / 2.f,
									0, 1, 0, -(top + bottom) / 2.f,
									0, 0, 1, -(nearPlane + farPlane) / 2.f,
									0, 0, 0, 1 };
	Mat4 orthoTranslate(arrOrthoTranslate);
	float arrOrthoScale[16] = { 2.f / (right - left), 0, 0, 0,
									0, 2.f / (top - bottom), 0, 0,
									0, 0, 2.f / (farPlane - nearPlane), 0,
									0, 0, 0, 1 };
	Mat4 orthoScale(arrOrthoScale);

	return orthoScale * orthoTranslate;;
}