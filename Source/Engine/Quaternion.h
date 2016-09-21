#pragma once

//created using reference from http://www.cprogramming.com/tutorial/3d/quaternions.html

class Quaternion
{
public:
	Quaternion(float aX = 0.0f, float aY = 0.0f, float aZ = 0.0f, float aW = 1.0f);
	void Normalize();

	void RotateAlongAxis(const Vector3f& aAxis, float aRotationAmount);
	void Rotate(const Vector3f& aRotationAmount);
	void RotateX(float aRotationAmount);
	void RotateY(float aRotationAmount);
	void RotateZ(float aRotationAmount);

	//note: (Q1*Q2) != (Q2*Q1)
	Quaternion operator *(const Quaternion& aRight) const;

	//note: (Q1*Q2) != (Q2*Q1)
	Quaternion& operator *=(const Quaternion& aRight);

	//this assumes the quaternion is normalized
	Matrix44f GenerateMatrix() const;
private:
	Vector3f myRotation;
	float myRotationAmount;
};
