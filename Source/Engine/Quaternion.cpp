#include "stdafx.h"
#include "Quaternion.h"

Quaternion::Quaternion(float aX, float aY, float aZ, float aW)
{
	float magnitude = Vector4f(aX, aY, aZ, aW).Length();
	x = aX / magnitude;
	y = aY / magnitude;
	z = aZ / magnitude;
	w = aW / magnitude;
}

void Quaternion::Normalize()
{
	*this = GetNormalized();
}

Quaternion Quaternion::GetNormalized() const
{
	return Quaternion(x, y, z, w);
}

void Quaternion::RotateAlongAxis(const Vector3f &aAxis, float aRotationAmount)
{
	float halfAngle = sinf(aRotationAmount / 2.f);

	Quaternion localRotation;
	localRotation.x = aAxis.x * halfAngle;
	localRotation.y = aAxis.y * halfAngle;
	localRotation.z = aAxis.z * halfAngle;
	localRotation.w = cosf(aRotationAmount / 2.f);

	*this = localRotation * *this;
	Normalize();
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
	Quaternion returnValue;
	returnValue.x = w * aRight.x + x * aRight.w  + y * aRight.z - z * aRight.y;
	returnValue.y = w * aRight.y - x * aRight.z + y * aRight.w + z * aRight.x;
	returnValue.z = w * aRight.z + x * aRight.y - y * aRight.x + z * aRight.w;
	returnValue.w = w * aRight.w - x * aRight.x - y * aRight.y - z * aRight.z;
	returnValue.Normalize();
	return returnValue;
}

Quaternion& Quaternion::operator*=(const Quaternion& aRight)
{
	return *this = *this * aRight;
}

Matrix44f Quaternion::GenerateMatrix() const
{
	//Shamefully stolen from http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
	float X = x;
	float Y = y;
	float Z = z;
	float W = w;
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

Vector3f Quaternion::GetLeft() const
{
	return -GetRight();
}

Vector3f Quaternion::GetRight() const
{
	return Vector3f(1.f, 0.f, 0.f) * *this;
}

Vector3f Quaternion::GetForward() const
{
	return Vector3f(0.f, 0.f, 1.f) * *this;
}

Vector3f Quaternion::GetBackward() const
{
	return -GetForward();
}

Vector3f Quaternion::GetUpward() const
{
	return Vector3f(0.f, 1.f, 0.f) * *this;
}

Vector3f Quaternion::GetDownward() const
{
	return -GetUpward();
}
