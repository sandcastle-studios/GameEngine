#include "stdafx.h"
#include "Camera.h"
#include "ConstantBuffer.h"

Camera::Camera()
{
	myCameraCB = std::make_unique<ConstantBuffer<CameraCB>>();
	myYaw = 0.f;
	myPitch = 0.f;
}

Camera::~Camera()
{
}

void Camera::CreatePerspective(float aVerticalFoVInDegrees, float aProjectionWidth, float aProjectionHeight, float aNearPlane, float aFarPlane)
{
	myProjection = Matrix44f::CreateProjection(aVerticalFoVInDegrees, aProjectionWidth, aProjectionHeight, aFarPlane, aNearPlane);
}

const ConstantBuffer<CameraCB> & Camera::GetCameraConstantBuffer() const
{
	return *myCameraCB;
}

void Camera::ApplyToVS() const
{
	UpdateCB();

	myCameraCB->BindToVS(0);
}

void Camera::UpdateCB() const
{
	CameraCB cb;
	cb.projection = myProjection;
	cb.view = Matrix44f::CreateRotateAroundX(-myPitch) * Matrix44f::CreateRotateAroundY(myYaw) * Matrix44f::CreateTranslation(myPosition);
	cb.view.Inverse();
	cb.cameraPosition = myPosition;
	myCameraCB->UpdateData(cb);
}

void Camera::ApplySkyboxMatrixToVS() const
{
	CameraCB cb;
	cb.projection = myProjection;
	cb.view = Matrix44f::CreateRotateAroundX(-myPitch) * Matrix44f::CreateRotateAroundY(myYaw);
	cb.view.Inverse();
	cb.cameraPosition = myPosition;
	myCameraCB->UpdateData(cb);
}

void Camera::LookAt(const Vector3f & aLookAt)
{
	Vector3f delta = aLookAt - GetPosition();
	Vector3f unit = delta.GetNormalized();
	myYaw = HalfPi - std::atan2f(delta.z, delta.x);
	myPitch = std::asinf(unit.y);
}
