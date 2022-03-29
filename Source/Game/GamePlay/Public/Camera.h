#pragma once

#include "Entity.h"
#include "Core/Math/Public/MathUtil.h"

using namespace Lumen::Core;

namespace Lumen::Game
{
    // Left hand
    /////////////////////////////
    //                         //
    //    y(j)|  / z(k)        //
    //        | /              //
    //        |/__ __ __ x(i)  //
    //                         //
    /////////////////////////////
    class Camera : public Entity
    {
    public:
        Camera(float fov, float aspect, float nearPlane, float farPlane);
        void Update();
        void UpdateProjMatrix();

        inline Mat4 GetViewMatrix() const noexcept { return mViewMatrix; }
        inline Mat4 GetProjMatrix() const noexcept { return mProjMatrix; }
        inline Mat4 GetViewProjMatrix() const noexcept { return mViewProjMatrix; }

        inline Vec3 GetPos() const noexcept { return mPos; }
        inline float GetNearZ() const noexcept { return mNearPlane; }
        inline float GetFarZ() const noexcept { return mFarPlane; }

    private:
        // Modularization later
        Mat4 mViewMatrix = Mat4(1.f);
        Mat4 mProjMatrix = Mat4(1.f);
        Mat4 mViewProjMatrix = Mat4(1.f);

        Vec3 mPos = Vec3(-6.f, 6.f, -6.f);
        Vec3 mUp = Vec3(0.f, 1.f, 0.f);
        Vec3 mFront = Vec3(1.f, -1.f, 1.f);

        float mFov = 0;
        float mAspectRatio = 0;
        float mNearPlane = 0;
        float mFarPlane = 0;
    };
}