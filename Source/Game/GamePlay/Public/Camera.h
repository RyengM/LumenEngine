#pragma once

#include "Entity.h"
#include "Core/Math/Public/MathUtil.h"
#include "Game/Engine/Public/DeviceStatus.h"

using namespace Lumen::Core;

namespace Lumen::Game
{
    /////////////////////////////
    //        LEFT HAND        //
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

        // IO
        void ProcessMouseMovement();
        void ProcessKeyboard();

        // Get / Set
        inline Mat4 GetViewMatrix() const noexcept { return mViewMatrix; }
        inline Mat4 GetProjMatrix() const noexcept { return mProjMatrix; }
        inline Mat4 GetViewProjMatrix() const noexcept { return mViewProjMatrix; }

        inline void SetPos(const Vec3& pos) noexcept { mTransform.position = pos; Update(); }
        inline Vec3 GetPos() const noexcept { return mTransform.position; }
        inline float GetNearZ() const noexcept { return mNearPlane; }
        inline float GetFarZ() const noexcept { return mFarPlane; }

    private:
        void UpdateRotateVector();

    public:
        std::shared_ptr<DeviceStatus> deviceStatus;

    private:
        // Matrix
        Mat4 mViewMatrix = Mat4(1.f);
        Mat4 mProjMatrix = Mat4(1.f);
        Mat4 mViewProjMatrix = Mat4(1.f);

        // Euler vector
        [[serialize(true)]]
        Vec3 mUp = Vec3(0.f, 1.f, 0.f);
        [[serialize(true)]]
        Vec3 mFront = Vec3(0.f, 0.f, 1.f);
        Vec3 mRight = Vec3(1.f, 0.f, 0.f);

        // Assume world up is always up _orz
        Vec3 mWorldUp = Vec3(0.f, 1.f, 0.f);

        // Config params
        [[serialize(true)]]
        float mFov = 0;
        [[serialize(true)]]
        float mAspectRatio = 0;
        [[serialize(true)]]
        float mNearPlane = 0;
        [[serialize(true)]]
        float mFarPlane = 0;
        [[serialize(true)]]
        float mMoveSpeed = 0.2f;

        // Rotation params
        float mYaw = 0.f;
        float mPitch = 0.f;

        RTTR_REGISTRATION_FRIEND
        RTTR_ENABLE(Entity)
    };
}