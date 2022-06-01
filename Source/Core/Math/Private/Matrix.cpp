#include "Core/Math/Public/Matrix.h"

using namespace Lumen::Core;

Mat3::Mat3(const float input[9])
{
	for (int i = 0; i < 9; ++i)
		data[i / 3][i % 3] = input[i];
}

Mat3::Mat3(float digit)
{
	data[0][0] = digit;
	data[0][1] = 0;
	data[0][2] = 0;
	data[1][0] = 0;
	data[1][1] = digit;
	data[1][2] = 0;
	data[2][0] = 0;
	data[2][1] = 0;
	data[2][2] = digit;
}

Mat3::Mat3(const Vec3& v0, const Vec3& v1, const Vec3& v2)
{
	data[0][0] = v0.x;
	data[0][1] = v1.x;
	data[0][2] = v2.x;
	data[1][0] = v0.y;
	data[1][1] = v1.y;
	data[1][2] = v2.y;
	data[2][0] = v0.z;
	data[2][1] = v1.z;
	data[2][2] = v2.z;
}

void Mat3::Clear()
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			data[i][j] = 0;
}

float Mat3::At(int x, int y) const
{
	return data[x][y];
}

void Mat3::SetElement(int x, int y, float value)
{
	data[x][y] = value;
}

Mat3 Mat3::operator*(const Mat3& m) const
{
	Mat3 mat;
	mat.data[0][0] = data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0] + data[0][2] * m.data[2][0];
	mat.data[0][1] = data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1] + data[0][2] * m.data[2][1];
	mat.data[0][2] = data[0][0] * m.data[0][2] + data[0][1] * m.data[1][2] + data[0][2] * m.data[2][2];

	mat.data[1][0] = data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0] + data[1][2] * m.data[2][0];
	mat.data[1][1] = data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1] + data[1][2] * m.data[2][1];
	mat.data[1][2] = data[1][0] * m.data[0][2] + data[1][1] * m.data[1][2] + data[1][2] * m.data[2][2];

	mat.data[2][0] = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0] + data[2][2] * m.data[2][0];
	mat.data[2][1] = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1] + data[2][2] * m.data[2][1];
	mat.data[2][2] = data[2][0] * m.data[0][2] + data[2][1] * m.data[1][2] + data[2][2] * m.data[2][2];

	return mat;
}

Vec3 Mat3::operator*(const Vec3& v) const
{
	Vec3 vec;
	vec.x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z;
	vec.y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z;
	vec.z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z;

	return vec;
}

Mat3 Mat3::Transpose() const
{
	Mat3 mat;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			mat.data[i][j] = data[j][i];
	return mat;
}

Mat4::Mat4(const float input[16])
{
	for (int i = 0; i < 16; ++i)
		data[i / 4][i % 4] = input[i];
}

Mat4::Mat4(float digit)
{
	data[0][0] = digit;
	data[0][1] = 0;
	data[0][2] = 0;
	data[0][3] = 0;
	data[1][0] = 0;
	data[1][1] = digit;
	data[1][2] = 0;
	data[1][3] = 0;
	data[2][0] = 0;
	data[2][1] = 0;
	data[2][2] = digit;
	data[2][3] = 0;
	data[3][0] = 0;
	data[3][1] = 0;
	data[3][2] = 0;
	data[3][3] = digit;
}

Mat4& Mat4::Translate(const Vec3& v)
{
	data[0][3] += v.x;
	data[1][3] += v.y;
	data[2][3] += v.z;
	return *this;
}

Mat4& Mat4::Scale(const Vec3& v)
{
	data[0][0] *= v.x;
	data[1][1] *= v.y;
	data[2][2] *= v.z;
	return *this;
}

void Mat4::Clear()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			data[i][j] = 0;
}

float Mat4::At(int x, int y) const
{
	return data[x][y];
}

void Mat4::SetElement(int x, int y, float value)
{
	data[x][y] = value;
}

Mat4 Mat4::operator*(const Mat4& m) const
{
	Mat4 mat;
	mat.data[0][0] = data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0] + data[0][2] * m.data[2][0] + data[0][3] * m.data[3][0];
	mat.data[0][1] = data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1] + data[0][2] * m.data[2][1] + data[0][3] * m.data[3][1];
	mat.data[0][2] = data[0][0] * m.data[0][2] + data[0][1] * m.data[1][2] + data[0][2] * m.data[2][2] + data[0][3] * m.data[3][2];
	mat.data[0][3] = data[0][0] * m.data[0][3] + data[0][1] * m.data[1][3] + data[0][2] * m.data[2][3] + data[0][3] * m.data[3][3];

	mat.data[1][0] = data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0] + data[1][2] * m.data[2][0] + data[1][3] * m.data[3][0];
	mat.data[1][1] = data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1] + data[1][2] * m.data[2][1] + data[1][3] * m.data[3][1];
	mat.data[1][2] = data[1][0] * m.data[0][2] + data[1][1] * m.data[1][2] + data[1][2] * m.data[2][2] + data[1][3] * m.data[3][2];
	mat.data[1][3] = data[1][0] * m.data[0][3] + data[1][1] * m.data[1][3] + data[1][2] * m.data[2][3] + data[1][3] * m.data[3][3];

	mat.data[2][0] = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0] + data[2][2] * m.data[2][0] + data[2][3] * m.data[3][0];
	mat.data[2][1] = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1] + data[2][2] * m.data[2][1] + data[2][3] * m.data[3][1];
	mat.data[2][2] = data[2][0] * m.data[0][2] + data[2][1] * m.data[1][2] + data[2][2] * m.data[2][2] + data[2][3] * m.data[3][2];
	mat.data[2][3] = data[2][0] * m.data[0][3] + data[2][1] * m.data[1][3] + data[2][2] * m.data[2][3] + data[2][3] * m.data[3][3];

	mat.data[3][0] = data[3][0] * m.data[0][0] + data[3][1] * m.data[1][0] + data[3][2] * m.data[2][0] + data[3][3] * m.data[3][0];
	mat.data[3][1] = data[3][0] * m.data[0][1] + data[3][1] * m.data[1][1] + data[3][2] * m.data[2][1] + data[3][3] * m.data[3][1];
	mat.data[3][2] = data[3][0] * m.data[0][2] + data[3][1] * m.data[1][2] + data[3][2] * m.data[2][2] + data[3][3] * m.data[3][2];
	mat.data[3][3] = data[3][0] * m.data[0][3] + data[3][1] * m.data[1][3] + data[3][2] * m.data[2][3] + data[3][3] * m.data[3][3];

	return mat;
}

Vec4 Mat4::operator*(const Vec4& v) const
{
	Vec4 vec;
	vec.x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z + data[0][3] * v.w;
	vec.y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z + data[1][3] * v.w;
	vec.z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z + data[2][3] * v.w;
	vec.w = data[3][0] * v.x + data[3][1] * v.y + data[3][2] * v.z + data[3][3] * v.w;

	return vec;
}

Vec3 Mat4::operator*(const Vec3& v) const
{
	Vec3 vec;
	vec.x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z;
	vec.y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z;
	vec.z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z;

	return vec;
}

Mat4 Mat4::HomogeneousInverse() const
{
	// rotateScaleMat * translateMat
	Mat4 mat;
	mat.data[0][0] = data[0][0];
	mat.data[0][1] = data[1][0];
	mat.data[0][2] = data[2][0];
	mat.data[0][3] = -data[0][0] * data[0][3] - data[1][0] * data[1][3] - data[2][0] * data[2][3];

	mat.data[1][0] = data[0][1];
	mat.data[1][1] = data[1][1];
	mat.data[1][2] = data[2][1];
	mat.data[1][3] = -data[0][1] * data[0][3] - data[1][1] * data[1][3] - data[2][1] * data[2][3];

	mat.data[2][0] = data[0][2];
	mat.data[2][1] = data[1][2];
	mat.data[2][2] = data[2][2];
	mat.data[2][3] = -data[0][2] * data[0][3] - data[1][2] * data[1][3] - data[2][2] * data[2][3];

	mat.data[3][0] = 0;
	mat.data[3][1] = 0;
	mat.data[3][2] = 0;
	mat.data[3][3] = 1;

	return mat;
}

Mat4 Mat4::Transpose() const
{
	Mat4 mat;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			mat.data[i][j] = data[j][i];
	return mat;
}

// This following is generated by Ubpa::USRefl::AutoRefl

using namespace Lumen::Core;

RTTR_REGISTRATION
{
	registration::class_<Lumen::Core::Mat3>("Mat3")
		//.property("data", &Mat3::data)	// C2664 under c++20
		.constructor<>()
		.constructor<const float>()
		.constructor<float>()
		.constructor<const Vec3&, const Vec3&, const Vec3&>()
		.method("operator*", select_overload<Mat3(const Mat3&) const>(&Mat3::operator*))
		.method("operator*", select_overload<Vec3(const Vec3&) const>(&Mat3::operator*))
		.method("Transpose", &Mat3::Transpose)
		.method("At", &Mat3::At)
		.method("SetElement", &Mat3::SetElement)
		.method("Clear", &Mat3::Clear)
	;
	registration::class_<Lumen::Core::Mat4>("Mat4")
		//.property("data", &Mat4::data)
		.constructor<>()
		.constructor<const float>()
		.constructor<float>()
		.method("operator*", select_overload<Mat4(const Mat4&) const>(&Mat4::operator*))
		.method("operator*", select_overload<Vec4(const Vec4&) const>(&Mat4::operator*))
		.method("operator*", select_overload<Vec3(const Vec3&) const>(&Mat4::operator*))
		.method("HomogeneousInverse", &Mat4::HomogeneousInverse)
		.method("Transpose", &Mat4::Transpose)
		.method("Translate", &Mat4::Translate)
		.method("Scale", &Mat4::Scale)
		.method("At", &Mat4::At)
		.method("SetElement", &Mat4::SetElement)
		.method("Clear", &Mat4::Clear)
	;
}