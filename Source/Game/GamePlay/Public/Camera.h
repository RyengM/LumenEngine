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
        Camera();
        Camera(float fov, float aspect, float nearPlane, float farPlane);
        void Update();
        void UpdateProjMatrix();

        inline Mat4 GetViewMatrix() const noexcept { return mViewMatrix; }
        inline Mat4 GetProjMatrix() const noexcept { return mProjMatrix; }
        inline Mat4 GetViewProjMatrix() const noexcept { return mViewProjMatrix; }

        inline void SetPos(const Vec3& pos) noexcept { mTransform.position = pos; Update(); }
        inline Vec3 GetPos() const noexcept { return mTransform.position; }
        inline float GetNearZ() const noexcept { return mNearPlane; }
        inline float GetFarZ() const noexcept { return mFarPlane; }

    private:
        Mat4 mViewMatrix = Mat4(1.f);
        Mat4 mProjMatrix = Mat4(1.f);
        Mat4 mViewProjMatrix = Mat4(1.f);

        [[serialize(true)]]
        Vec3 mUp = Vec3(0.f, 1.f, 0.f);
        [[serialize(true)]]
        Vec3 mFront = Vec3(1.f, -1.f, 1.f);

        [[serialize(true)]]
        float mFov = 0;
        [[serialize(true)]]
        float mAspectRatio = 0;
        [[serialize(true)]]
        float mNearPlane = 0;
        [[serialize(true)]]
        float mFarPlane = 0;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(Entity)
    };
}