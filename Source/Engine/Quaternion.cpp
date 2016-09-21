#include "stdafx.h"
#include "Quaternion.h"

Quaternion::Quaternion(float aX, float aY, float aZ, float aW)
{
	myRotation.x = aX;
	myRotation.y = aY;
	myRotation.z = aZ;
	myRotationAmount = aW;

	Normalize();
}

void Quaternion::Normalize()
{
	float magnitude = myRotation.Length();
	
	myRotation.x /= magnitude;
	myRotation.y /= magnitude;
	myRotation.z /= magnitude;
	myRotationAmount /= magnitude;
}

void Quaternion::RotateAlongAxis(const Vector3f &aAxis, float aRotationAmount)
{
	/*
	local_rotation.x = axis.x * sinf(fAngle / 2)
	local_rotation.y = axis.y * sinf(fAngle / 2)
	local_rotation.z = axis.z * sinf(fAngle / 2)
	local_rotation.w = cosf(fAngle / 2)
	*/

	Quaternion localRotation;
	localRotation.myRotation.x = aAxis.x * sinf(aRotationAmount / 2.f);
	localRotation.myRotation.y = aAxis.y * sinf(aRotationAmount / 2.f);
	localRotation.myRotation.z = aAxis.z * sinf(aRotationAmount / 2.f);
	localRotation.myRotationAmount = cosf(aRotationAmount / 2.f);

	*this = localRotation * *this;
}

void Quaternion::Rotate(const Vector3f& aRotationAmount)
{
	float magnitude = aRotationAmount.Length();
	Vector3f rotationNormalized = aRotationAmount.GetNormalized();
		
	RotateAlongAxis(rotationNormalized, magnitude);
}

void Quaternion::RotateX(float aRotationAmount)
{
	RotateAlongAxis(Vector3f(1.0f, 0.0f, 0.0f), aRotationAmount);
}

void Quaternion::RotateY(float aRotationAmount)
{
	RotateAlongAxis(Vector3f(0.0f, 1.0f, 0.0f), aRotationAmount);
}

void Quaternion::RotateZ(float aRotationAmount)
{
	RotateAlongAxis(Vector3f(0.0f, 0.0f, 1.0f), aRotationAmount);
}

Quaternion Quaternion::operator*(const Quaternion& aRight) const
{
	/*
	(Q1 * Q2).x = (w1*x2 + x1*w2 + y1*z2 - z1*y2)
	(Q1 * Q2).y = (w1*y2 - x1*z2 + y1*w2 + z1*x2)
	(Q1 * Q2).z = (w1*z2 + x1*y2 - y1*x2 + z1*w2)
	(Q1 * Q2).w = (w1*w2 - x1*x2 - y1*y2 - z1*z2)
	*/

	Quaternion returnValue;
	returnValue.myRotation.x = myRotationAmount * aRight.myRotation.x + myRotation.x * aRight.myRotationAmount  + myRotation.y * aRight.myRotation.z - myRotation.z * aRight.myRotation.y;

	returnValue.myRotation.y = myRotationAmount * aRight.myRotation.y - myRotation.x * aRight.myRotation.z + myRotation.y * aRight.myRotationAmount + myRotation.z * aRight.myRotation.x;

	returnValue.myRotation.z = myRotationAmount * aRight.myRotation.z + myRotation.x * aRight.myRotation.y - myRotation.y * aRight.myRotation.x + myRotation.z * aRight.myRotationAmount;

	returnValue.myRotationAmount = myRotationAmount * aRight.myRotationAmount - myRotation.x * aRight.myRotation.x - myRotation.y * aRight.myRotation.y - myRotation.z * aRight.myRotation.z;

	return returnValue;
}

Quaternion& Quaternion::operator*=(const Quaternion& aRight)
{
	return *this = *this * aRight;
}

Matrix44f Quaternion::GenerateMatrix() const
{
	//Shamefully stolen from http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
	float X = myRotation.x;
	float Y = myRotation.y;
	float Z = myRotation.z;
	float W = myRotationAmount;
	float xx = X * X;
	float xy = X * Y;
	float xz = X * Z;
	float xw = X * W;
	float yy = Y * Y;
	float yz = Y * Z;
	float yw = Y * W;
	float zz = Z * Z;
	float zw = Z * W;

	Matrix44f returnValue;
	returnValue.m11 = 1 - 2 * (yy + zz);
	returnValue.m12 = 2 * (xy - zw);
	returnValue.m13 = 2 * (xz + yw);

	returnValue.m21 = 2 * (xy + zw);
	returnValue.m22 = 1 - 2 * (xx + zz);
	returnValue.m23 = 2 * (yz - xw);

	returnValue.m31 = 2 * (xz - yw);
	returnValue.m32 = 2 * (yz + xw);
	returnValue.m33 = 1 - 2 * (xx + yy);

	returnValue.m14 = returnValue.m24 = returnValue.m34 = returnValue.m41 = returnValue.m42 = returnValue.m43 = 0;
	returnValue.m44 = 1;

	return returnValue;
}
