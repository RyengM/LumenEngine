#include "Game/GamePlay/Public/Camera.h"

using namespace Lumen::Game;

Camera::Camera(float fov, float aspect, float nearPlane, float farPlane)
{
	mFov = fov;
	mAspectRatio = aspect;
	mNearPlane = nearPlane;
	mFarPlane = farPlane;

	UpdateProjMatrix();
	Update();
}

void Camera::Update()
{
	mViewMatrix = MathUtil::LookAt(mPos, mPos + mFront, Vec3(0, 1, 0));
	mViewProjMatrix = mProjMatrix * mViewMatrix;
}

void Camera::UpdateProjMatrix()
{
	float angle = MathUtil::Angle2Radian(mFov);
	float top = tan(angle / 2.f) * mNearPlane;
	float bottom = -top;
	float right = top * mAspectRatio;
	float left = -right;

	float arrOrthoTranslate[16] = { 1, 0, 0, -(left + right) / 2.f,
										  0, 1, 0, -(top + bottom) / 2.f,
										  0, 0, 1, -(mNearPlane + mFarPlane) / 2.f,
										  0, 0, 0, 1 };
	Mat4 orthoTranslate(arrOrthoTranslate);
	float arrOrthoScale[16] = { 2.f / (right - left), 0, 0, 0,
										  0, 2.f / (top - bottom), 0, 0,
										  0, 0, 2.f / (mFarPlane - mNearPlane), 0,
										  0, 0, 0, 1 };
	Mat4 orthoScale(arrOrthoScale);
	float arrOrtho2Perspective[16] = { mNearPlane, 0, 0, 0,
										  0, mNearPlane, 0, 0,
										  0, 0, mNearPlane + mFarPlane, -mNearPlane * mFarPlane,
										  0, 0, 1, 0 };
	Mat4 proj2ortho(arrOrtho2Perspective);
	Mat4 orthoMatrix = orthoScale * orthoTranslate;

	mProjMatrix = orthoMatrix * proj2ortho;
}