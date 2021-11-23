#pragma once

namespace Lumen::Core
{
	template<typename T>
	TVec2<T> TVec2<T>::operator+(const TVec2<T>& v) const
	{
		TVec2<T> vec2;
		vec2.x = x + v.x;
		vec2.y = y + v.y;
		return vec2;
	}

	template<typename T>
	TVec2<T> TVec2<T>::operator-(const TVec2<T>& v) const
	{
		TVec2<T> vec2;
		vec2.x = x - v.x;
		vec2.y = y - v.y;
		return vec2;
	}

	template<typename T>
	TVec2<T> TVec2<T>::operator*(const T num) const
	{
		TVec2<T> vec2;
		vec2.x = x * num;
		vec2.y = y * num;
		return vec2;
	}

	template<typename T>
	TVec2<T> TVec2<T>::operator/(const T num) const
	{
		TVec2<T> vec2;
		T invn = 1 / num;
		vec2.x = x * invn;
		vec2.y = y * invn;
		return vec2;
	}

	template<typename T>
	TVec2<T>& TVec2<T>::operator+=(const TVec2<T>& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	template<typename T>
	TVec2<T>& TVec2<T>::operator-=(const TVec2<T>& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	template<typename T>
	TVec2<T>& TVec2<T>::operator*=(const T num)
	{
		x *= num;
		y *= num;
		return *this;
	}

	template<typename T>
	TVec2<T>& TVec2<T>::operator/=(const T num)
	{
		T invn = 1 / num;
		x *= invn;
		y *= invn;
		return *this;
	}

	template<typename T>
	void TVec2<T>::Serialize(Archive& ar)
	{
		ar.BeginObject();
		ar << "x" << x;
		ar << "y" << y;
		ar.EndObject();
	}

	template<typename T>
	T TVec2<T>::Dot(const TVec2<T>& v) const
	{
		return x * v.x + y * v.y;
	}

	template<typename T>
	T TVec2<T>::Length()
	{
		return sqrt(x * x + y * y);
	}

	template<typename T>
	TVec2<T> TVec2<T>::Normalize()
	{
		TVec2<T> vec2;
		T invn = 1 / Length();
		vec2.x = x * invn;
		vec2.y = y * invn;
		return vec2;
	}

	template<typename T>
	TVec3<T> TVec3<T>::operator-(void)
	{
		TVec3<T> vec3;
		vec3.x = -x;
		vec3.y = -y;
		vec3.z = -z;
		return vec3;
	}

	template<typename T>
	TVec3<T> TVec3<T>::operator+(const TVec3<T>& v) const
	{
		TVec3<T> vec3;
		vec3.x = x + v.x;
		vec3.y = y + v.y;
		vec3.z = z + v.z;
		return vec3;
	}

	template<typename T>
	TVec3<T> TVec3<T>::operator-(const TVec3<T>& v) const
	{
		TVec3 vec3;
		vec3.x = x - v.x;
		vec3.y = y - v.y;
		vec3.z = z - v.z;
		return vec3;
	}

	template<typename T>
	TVec3<T> TVec3<T>::operator*(const T num) const
	{
		TVec3<T> vec3;
		vec3.x = x * num;
		vec3.y = y * num;
		vec3.z = z * num;
		return vec3;
	}

	template<typename T>
	TVec3<T> TVec3<T>::operator/(const T num) const
	{
		TVec3<T> vec3;
		T invNum = 1 / num;
		vec3.x = x * invNum;
		vec3.y = y * invNum;
		vec3.z = z * invNum;
		return vec3;
	}

	template<typename T>
	TVec3<T>& TVec3<T>::operator+=(const TVec3<T>& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	template<typename T>
	TVec3<T>& TVec3<T>::operator-=(const TVec3<T>& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	template<typename T>
	TVec3<T>& TVec3<T>::operator*=(const T num)
	{
		x *= num;
		y *= num;
		z *= num;
		return *this;
	}

	template<typename T>
	TVec3<T>& TVec3<T>::operator/=(const T num)
	{
		T invNum = 1 / num;
		x *= invNum;
		y *= invNum;
		z *= invNum;
		return *this;
	}

	template<typename T>
	bool TVec3<T>::operator==(const TVec3<T>& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	template<typename T>
	void TVec3<T>::Serialize(Archive& ar)
	{
		ar.BeginObject();
		ar << "x" << x;
		ar << "y" << y;
		ar << "z" << z;
		ar.EndObject();
	}

	template<typename T>
	T TVec3<T>::SqrLength()
	{
		return x * x + y * y + z * z;
	}

	template<typename T>
	T TVec3<T>::Length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	template<typename T>
	TVec3<T> TVec3<T>::Normalize()
	{
		TVec3 vec3;
		T invn = 1 / Length();
		vec3.x = x * invn;
		vec3.y = y * invn;
		vec3.z = z * invn;
		return vec3;
	}

	template<typename T>
	T TVec3<T>::Dot(const TVec3<T>& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	template<typename T>
	TVec3<T> TVec3<T>::Cross(const TVec3<T>& v) const
	{
		TVec3 vec3;
		vec3.x = y * v.z - z * v.y;
		vec3.y = z * v.x - x * v.z;
		vec3.z = x * v.y - y * v.x;
		return vec3;
	}

	template<typename T>
	TVec3<T> TVec3<T>::ElementProduct(const TVec3<T>& v) const
	{
		TVec3<T> vec3;
		vec3.x = x * v.x;
		vec3.y = y * v.y;
		vec3.z = z * v.z;
		return vec3;
	}

	template<typename T>
	TVec2<T> TVec3<T>::xy() const
	{
		TVec2<T> vec2;
		vec2.x = x;
		vec2.y = y;
		return vec2;
	}

	template<typename T>
	TVec4<T>::TVec4(const TVec3<T>& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = 1;
	}

	template<typename T>
	TVec4<T>::TVec4(const TVec3<T>& v, T w) : w(w)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	template<typename T>
	TVec4<T>::TVec4(const TVec2<T>& v, T z, T w) : z(z), w(w)
	{
		x = v.x;
		y = v.y;
	}

	template<typename T>
	void TVec4<T>::Serialize(Archive& ar)
	{
		ar.BeginObject();
		ar << "x" << x;
		ar << "y" << y;
		ar << "z" << z;
		ar << "w" << w;
		ar.EndObject();
	}

	template<typename T>
	TVec4<T> TVec4<T>::operator+(const TVec4<T>& v) const
	{
		TVec4<T> vec4;
		vec4.x = x + v.x;
		vec4.y = y + v.y;
		vec4.z = z + v.z;
		vec4.w = w + v.w;
		return vec4;
	}

	template<typename T>
	TVec4<T> TVec4<T>::operator-(const TVec4<T>& v) const
	{
		TVec4<T> vec4;
		vec4.x = x - v.x;
		vec4.y = y - v.y;
		vec4.z = z - v.z;
		vec4.w = w - v.w;
		return vec4;
	}

	template<typename T>
	TVec4<T> TVec4<T>::operator*(const T num) const
	{
		TVec4<T> vec4;
		vec4.x = x * num;
		vec4.y = y * num;
		vec4.z = z * num;
		vec4.w = w * num;
		return vec4;
	}

	template<typename T>
	TVec4<T> TVec4<T>::operator/(const T num) const
	{
		TVec4<T> vec4;
		T invn = 1 / num;
		vec4.x = x * invn;
		vec4.y = y * invn;
		vec4.z = z * invn;
		vec4.w = w * invn;
		return vec4;
	}

	template<typename T>
	TVec4<T>& TVec4<T>::operator+=(const TVec4<T>& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	template<typename T>
	TVec4<T>& TVec4<T>::operator-=(const TVec4<T>& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	template<typename T>
	TVec4<T>& TVec4<T>::operator*=(const T num)
	{
		x *= num;
		y *= num;
		z *= num;
		w *= num;
		return *this;
	}

	template<typename T>
	TVec4<T>& TVec4<T>::operator/=(const T num)
	{
		T invn = 1 / num;
		x *= invn;
		y *= invn;
		z *= invn;
		w *= invn;
		return *this;
	}

	template<typename T>
	TVec3<T> TVec4<T>::xyz() const
	{
		TVec3<T> vec3;
		vec3.x = x;
		vec3.y = y;
		vec3.z = z;
		return vec3;
	}

	template<typename T>
	TVec2<T> TVec4<T>::xy() const
	{
		TVec2<T> vec2;
		vec2.x = x;
		vec2.y = y;
		return vec2;
	}
}