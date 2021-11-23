#pragma once

namespace Lumen::Core
{
	template <typename T>
	TMat3<T>::TMat3(const T input[9])
	{
		for (int i = 0; i < 9; ++i)
			data[i / 3][i % 3] = input[i];
	}

	template <typename T>
	TMat3<T>::TMat3(T digit)
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

	template <typename T>
	TMat3<T>::TMat3(const Vec3& v0, const Vec3& v1, const Vec3& v2)
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

	template <typename T>
	void TMat3<T>::Clear()
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				data[i][j] = 0;
	}

	template <typename T>
	T TMat3<T>::At(int x, int y) const
	{
		return data[x][y];
	}

	template <typename T>
	void TMat3<T>::SetElement(int x, int y, T value)
	{
		data[x][y] = value;
	}

	template <typename T>
	TMat3<T> TMat3<T>::operator*(const TMat3<T>& m) const
	{
		TMat3<T> mat;
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

	template <typename T>
	TVec3<T> TMat3<T>::operator*(const TVec3<T>& v) const
	{
		TVec3<T> vec;
		vec.x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z;
		vec.y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z;
		vec.z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z;

		return vec;
	}

	template <typename T>
	TMat3<T> TMat3<T>::Transpose() const
	{
		TMat3<T> mat;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				mat.data[i][j] = data[j][i];
		return mat;
	}

	template <typename T>
	TMat4<T>::TMat4(const T input[16])
	{
		for (int i = 0; i < 16; ++i)
			data[i / 4][i % 4] = input[i];
	}

	template <typename T>
	TMat4<T>::TMat4(T digit)
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

	template <typename T>
	TMat4<T>& TMat4<T>::Translate(const TVec3<T>& v)
	{
		data[0][3] += v.x;
		data[1][3] += v.y;
		data[2][3] += v.z;
		return *this;
	}

	template <typename T>
	TMat4<T>& TMat4<T>::Scale(const TVec3<T>& v)
	{
		data[0][0] *= v.x;
		data[1][1] *= v.y;
		data[2][2] *= v.z;
		return *this;
	}

	template <typename T>
	void TMat4<T>::Clear()
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				data[i][j] = 0;
	}

	template <typename T>
	T TMat4<T>::At(int x, int y) const
	{
		return data[x][y];
	}

	template <typename T>
	void TMat4<T>::SetElement(int x, int y, T value)
	{
		data[x][y] = value;
	}

	template <typename T>
	TMat4<T> TMat4<T>::operator*(const TMat4<T>& m) const
	{
		TMat4<T> mat;
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

	template <typename T>
	TVec4<T> TMat4<T>::operator*(const TVec4<T>& v) const
	{
		TVec4<T> vec;
		vec.x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z + data[0][3] * v.w;
		vec.y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z + data[1][3] * v.w;
		vec.z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z + data[2][3] * v.w;
		vec.w = data[3][0] * v.x + data[3][1] * v.y + data[3][2] * v.z + data[3][3] * v.w;

		return vec;
	}

	template <typename T>
	TVec3<T> TMat4<T>::operator*(const TVec3<T>& v) const
	{
		TVec3<T> vec;
		vec.x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z;
		vec.y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z;
		vec.z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z;

		return vec;
	}

	template <typename T>
	TMat4<T> TMat4<T>::HomogeneousInverse() const
	{
		// rotateScaleMat * translateMat
		TMat4<T> mat;
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

	template <typename T>
	TMat4<T> TMat4<T>::Transpose() const
	{
		TMat4<T> mat;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				mat.data[i][j] = data[j][i];
		return mat;
	}
}