#pragma once


//created using reference from http://www.cprogramming.com/tutorial/3d/quaternions.html

class Quaternion
{
public:
	Quaternion(float aX = 0.0f, float aY = 0.0f, float aZ = 0.0f, float aW = 1.f);

	void Normalize();
	Quaternion GetNormalized() const;

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

	Vector3f GetLeft() const;
	Vector3f GetRight() const;
	Vector3f GetForward() const;
	Vector3f GetBackward() const;
	Vector3f GetUpward() const;
	Vector3f GetDownward() const;

	float x, y, z, w;
};

inline Vector3f operator *(const Vector3f & aVector, const Quaternion & aQuaternion)
{
	Vector4f m = Vector4f(aVector, 1.f);
	m = m * aQuaternion.GetNormalized().GenerateMatrix();
	return Vector3f(m.x, m.y, m.z);
}

inline Vector3f & operator *=(Vector3f & aVector, const Quaternion & aQuaternion)
{
	aVector = aVector * aQuaternion;
	return aVector;
}
