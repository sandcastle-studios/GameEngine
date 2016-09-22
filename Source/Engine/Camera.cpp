#include "stdafx.h"
#include "Camera.h"
#include "Buffer\ConstantBuffer.h"

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
	Vector3f normal = (aLookAt - GetPosition()).GetNormalized();
	myRotation = Quaternion(normal.x, normal.y, normal.z);
}
