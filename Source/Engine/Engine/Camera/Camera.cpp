#include "stdafx.h"
#include "Engine\Camera\Camera.h"
#include "Engine\Buffer\ConstantBuffer.h"

Camera::Camera()
{
	myCameraCB = std::make_unique<ConstantBuffer<CameraCB>>();
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
	myCameraCB->BindToPS(0);
}

void Camera::UpdateCB() const
{
	Quaternion rotation = myRotation;
	rotation.Normalize();
	auto rotationMatrix = rotation.GenerateMatrix();

	CameraCB cb;
	cb.projection = myProjection;
	cb.view = rotationMatrix * Matrix44f::CreateTranslation(myPosition);
	cb.view.Inverse();
	cb.cameraPosition = myPosition;
	myCameraCB->UpdateData(cb);
}

void Camera::ApplySkyboxMatrixToVS() const
{
	Quaternion rotation = myRotation;
	rotation.Normalize();

	CameraCB cb;
	cb.projection = myProjection;
	cb.view = rotation.GenerateMatrix();
	cb.view.Inverse();
	cb.cameraPosition = myPosition;
	myCameraCB->UpdateData(cb);
}

void Camera::LookAt(const Vector3f & aLookAt)
{
	Vector3f forwardVector = Vector3f(aLookAt - myPosition).GetNormalized();

	float dot = Vector3f::Dot(Vector3f(0.f, 0.f, 1.f), forwardVector);

	if (abs(dot - (-1.0f)) < 0.000001f)
	{
		myRotation = Quaternion(0.f, 1.f, 0.f, Pi);
		return;
	}
	if (abs(dot - (1.0f)) < 0.000001f)
	{
		myRotation = Quaternion();
		return;
	}

	float rotAngle = acosf(dot);
	Vector3f rotAxis = Vector3f::Cross(Vector3f(0.f, 0.f, 1.f), forwardVector);
	rotAxis.Normalize();
	myRotation = Quaternion();
	myRotation.RotateAlongAxis(rotAxis, rotAngle);
}
