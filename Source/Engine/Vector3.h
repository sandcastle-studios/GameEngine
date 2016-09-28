#pragma once
#include <cmath>

template<typename TYPE>
class Vector4;

template<typename TYPE>
class Vector3
{
public:
	Vector3(void)
	{
		x = static_cast<TYPE>(0);
		y = static_cast<TYPE>(0);
		z = static_cast<TYPE>(0);
	}
	Vector3(const Vector3 &aVector3)
	{
		x = aVector3.x;
		y = aVector3.y;
		z = aVector3.z;
	}
	template<typename U> explicit Vector3(const Vector3<U> &aVector)
	{
		x = static_cast<TYPE>(aVector.x);
		y = static_cast<TYPE>(aVector.y);
		z = static_cast<TYPE>(aVector.z);
	}
	Vector3(const TYPE anX, const TYPE aY, const TYPE aZ)
	{
		x = anX;
		y = aY;
		z = aZ;
	}

	friend Vector3 operator +(Vector3 aLeft, const Vector3 &aRight)
	{
		return aLeft += aRight;
	}

	friend Vector3 operator -(Vector3 aLeft, const Vector3 &aRight)
	{
		return aLeft -= aRight;
	}


	friend Vector3 operator *(Vector3 aLeft, const TYPE aRight)
	{
		return aLeft *= aRight;
	}


	friend Vector3 operator /(Vector3 aLeft, const TYPE aRight)
	{
		return aLeft /= aRight;
	}

	friend Vector3 operator *(const TYPE aRight, Vector3 aLeft)
	{
		return aLeft *= aRight;
	}

	friend Vector3 operator *(const Vector3 aRight, Vector3 aLeft)
	{
		return aLeft *= aRight;
	}

	friend Vector3 operator /(const TYPE aRight, Vector3 aLeft)
	{
		return aLeft /= aRight;
	}

	friend Vector3 operator -(Vector3 aRight)
	{
		return aRight *= static_cast<TYPE>(-1);
	}

	friend bool operator ==(const Vector3 &aLeft, const Vector3 &aRight)
	{
		return aLeft.x == aRight.x &&
			aLeft.y == aRight.y &&
			aLeft.z == aRight.z;
	}

	friend bool operator !=(const Vector3 &aLeft, const Vector3 &aRight)
	{
		return (aLeft == aRight) == false;
	}

	Vector3 &operator =(const Vector3 &aRight)
	{
		x = aRight.x;
		y = aRight.y;
		z = aRight.z;
		return *this;
	}

	Vector3 &operator +=(const Vector3 &aRight)
	{
		x += aRight.x;
		y += aRight.y;
		z += aRight.z;
		return *this;
	}
	Vector3 &operator -=(const Vector3 &aRight)
	{
		x -= aRight.x;
		y -= aRight.y;
		z -= aRight.z;
		return *this;
	}
	Vector3 &operator *=(const TYPE aRight)
	{
		x *= aRight;
		y *= aRight;
		z *= aRight;
		return *this;
	}
	Vector3 &operator *=(const Vector3 aRight)
	{
		x *= aRight.x;
		y *= aRight.y;
		z *= aRight.z;
		return *this;
	}

	Vector3 &operator /=(const TYPE aRight)
	{
		x /= aRight;
		y /= aRight;
		z /= aRight;
		return *this;
	}

	TYPE Length(void) const
	{
		return static_cast<TYPE>(sqrt(x * x + y * y + z * z));
	}
	TYPE Length2(void) const
	{
		TYPE length = Length();
		return length * length;
	}
	TYPE Dot(const Vector3 &aRight) const
	{
		return x * aRight.x +
			y * aRight.y +
			z * aRight.z;
	}
	Vector3 Cross(const Vector3 &aRight) const
	{
		return Vector3(y * aRight.z - z * aRight.y,
			z * aRight.x - x * aRight.z,
			x * aRight.y - y * aRight.x);
	}
	Vector3 GetNormalized(void) const
	{
		return *this / Length();
	}

	Vector3 &Normalize(void)
	{
		*this = GetNormalized();
		return *this;
	}

	TYPE x,
		y,
		z;

	static TYPE Dot(const Vector3 &aLeft, const Vector3 &aRight)
	{
		return aLeft.Dot(aRight);
	}
	static Vector3 Cross(const Vector3 &aLeft, const Vector3 &aRight)
	{
		return aLeft.Cross(aRight);
	}
	static Vector3 Normalize(Vector3 aVector)
	{
		return aVector.GetNormalized();
	}

	operator Vector4<TYPE>() const
	{
		return Vector4<TYPE>(x, y, z, 1.f);
	}

	static const Vector3 Zero,
		UnitX,
		UnitY,
		UnitZ,
		One;
};

using Vector3c = Vector3 < char >;
using Vector3i = Vector3 < int >;
using Vector3ui = Vector3 < unsigned int >;
using Vector3f = Vector3 < float >;
using Vector3d = Vector3 < double >;

template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::Zero(0, 0, 0);
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitX(1, 0, 0);
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitY(0, 1, 0);
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitZ(0, 0, 1);
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::One(1, 1, 1);
