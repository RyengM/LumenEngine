#pragma once

#include "Core/Common/Public/BaseObject.h"

// It seems operator/= cannot be reflected by UANTLR correctly now. Try fix later

namespace Lumen::Core
{
    struct Vec2 : public BaseObject
    {
        [[serialize(true)]]
        float x, y;

        Vec2() : x(0), y(0) {};
        Vec2(float x, float y) : x(x), y(y) {};

        Vec2 operator+(const Vec2& v) const;
        Vec2 operator-(const Vec2& v) const;

        Vec2 operator*(const float num) const;
        Vec2 operator/(const float num) const;

        Vec2& operator+=(const Vec2& v);
        Vec2& operator-=(const Vec2& v);

        Vec2& operator*=(const float num);
        Vec2& operator/=(const float num);

        float Dot(const Vec2& v) const;

        float Length();
        Vec2 Normalize();

        RTTR_ENABLE(BaseObject)
    };

    struct Vec3 : public BaseObject
    {
        [[serialize(true)]]
        float x, y, z;

        Vec3() : x(0), y(0), z(0) {};
        Vec3(float num) : x(num), y(num), z(num) {};
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {};
        
        Vec3 operator-(void);

        Vec3 operator+(const Vec3& v) const;
        Vec3 operator-(const Vec3& v) const;

        Vec3 operator*(float num) const;
        Vec3 operator/(float num) const;

        Vec3& operator+=(const Vec3& v);
        Vec3& operator-=(const Vec3& v);

        Vec3& operator*=(float num);
        Vec3& operator/=(float num);

        bool operator==(const Vec3& v) const;

        float SqrLength();
        float Length();
        Vec3 Normalize();

        float Dot(const Vec3& v) const;
        Vec3 Cross(const Vec3& v) const;
        Vec3 ElementProduct(const Vec3& v) const;

        RTTR_ENABLE(BaseObject)
    };

    struct Vec4 : public BaseObject
    {
        [[serialize(true)]]
        float x, y, z, w;

        Vec4() : x(0), y(0), z(0), w(0) {};
        Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
        Vec4(const Vec3& v);
        Vec4(const Vec3& v, float w);

        Vec4 operator+(const Vec4& v) const;
        Vec4 operator-(const Vec4& v) const;

        Vec4 operator*(float num) const;
        Vec4 operator/(float num) const;

        Vec4& operator+=(const Vec4& v);
        Vec4& operator-=(const Vec4& v);

        Vec4& operator*=(float num);
        Vec4& operator/=(float num);

        Vec3 xyz() const;

        RTTR_ENABLE(BaseObject)
    };
}