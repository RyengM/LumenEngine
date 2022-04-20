#include "Core/Math/Public/Quaternion.h"

using namespace Lumen::Core;

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z)
{
	v = Vec3(x, y, z);
}

Quaternion::Quaternion(float theta, const Vec3& axis)
{
	w = cos(theta / 2.f);
	float coeff = sin(theta / 2.f);
	x = axis.x * coeff;
	y = axis.y * coeff;
	z = axis.z * coeff;
	v = Vec3(x, y, z);
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
	return Quaternion(w * q.w - v.Dot(q.v), v.Cross(q.v) + q.v * w + v * q.w);
}

Quaternion Quaternion::operator/(float num) const
{
	return Quaternion(w / num, x / num, y / num, z / num);
}

Quaternion Quaternion::Conjugate()
{
	return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::Inverse()
{
	return Conjugate() / (Vec3(x, y, z).SqrLength() + w * w);
}

Mat4 Quaternion::ToRotateMatrix()
{
	float arr[16] = { 1 - 2 * y * y - 2 * z * z	, 2 * x * y - 2 * z * w     , 2 * x * z + 2 * y * w		, 0.f,
					  2 * x * y + 2 * z * w		, 1 - 2 * x * x - 2 * z * z , 2 * y * z - 2 * x * w		, 0.f,
					  2 * x * z - 2 * y * w		, 2 * y * z + 2 * x * w     , 1 - 2 * x * x - 2 * y * y , 0.f,
					  0.f						, 0.f						, 0.f						, 1.f};
	return Mat4(arr);
}