#pragma once
#include <cmath>

namespace ENGINE_NAMESPACE
{

	template<typename TYPE>
	class Vector3;

	template<typename TYPE>
	class Vector4
	{
	public:
		Vector4()
		{
			x = static_cast<TYPE>(0);
			y = static_cast<TYPE>(0);
			z = static_cast<TYPE>(0);
			w = static_cast<TYPE>(0);
		}

		Vector4(const Vector4 &anOther)
		{
			*this = anOther;
		}

		Vector4(const Vector3<TYPE> &anOther, const TYPE aW)
		{
			*this = anOther;
			w = aW;
		}

		explicit Vector4(const Vector3<TYPE> &anOther)
		{
			*this = anOther;
		}

		template<typename U> explicit Vector4(const Vector4<U> &anOther)
		{
			x = static_cast<TYPE>(anOther.x);
			y = static_cast<TYPE>(anOther.y);
			z = static_cast<TYPE>(anOther.z);
			w = static_cast<TYPE>(anOther.w);
		}

		Vector4(const TYPE anX, const TYPE anY, const TYPE aZ, const TYPE aW)
		{
			x = anX;
			y = anY;
			z = aZ;
			w = aW;
		}

		friend Vector4 operator +(Vector4 aLeft, const Vector4 &aRight)
		{
			return aLeft += aRight;
		}

		friend Vector4 operator -(Vector4 aLeft, const Vector4 &aRight)
		{
			return aLeft -= aRight;
		}


		friend Vector4 operator *(Vector4 aLeft, const TYPE aRight)
		{
			return aLeft *= aRight;
		}

		friend Vector4 operator /(Vector4 aLeft, const TYPE aRight)
		{
			return aLeft /= aRight;
		}

		friend Vector4 operator *(const TYPE aRight, Vector4 aLeft)
		{
			return aLeft *= aRight;
		}

		friend Vector4 operator /(const TYPE aRight, Vector4 aLeft)
		{
			return aLeft /= aRight;
		}

		friend Vector4 operator -(Vector4 aRight)
		{
			return aRight * static_cast<TYPE>(-1);
		}

		friend bool operator ==(const Vector4 &aLeft, const Vector4 &aRight)
		{
			return (aLeft.x == aRight.x && aLeft.y == aRight.y &&
				aLeft.z == aRight.z && aLeft.w == aRight.w);
		}

		friend bool operator !=(const Vector4 &aLeft, const Vector4 &aRight)
		{
			return (aLeft == aRight) == false;
		}

		Vector4 &operator =(const Vector4 &aRight)
		{
			x = aRight.x;
			y = aRight.y;
			z = aRight.z;
			w = aRight.w;
			return *this;
		}
		Vector4 &operator =(const Vector3<TYPE> &aRight)
		{
			x = aRight.x;
			y = aRight.y;
			z = aRight.z;
			w = static_cast<TYPE>(1);
			return *this;
		}

		Vector4 &operator +=(const Vector4 &aRight)
		{
			x += aRight.x;
			y += aRight.y;
			z += aRight.z;
			w += aRight.w;
			return *this;
		}
		Vector4 &operator -=(const Vector4 &aRight)
		{
			x -= aRight.x;
			y -= aRight.y;
			z -= aRight.z;
			w -= aRight.w;
			return *this;
		}
		Vector4 &operator *=(const TYPE aRight)
		{
			x *= aRight;
			y *= aRight;
			z *= aRight;
			w *= aRight;
			return *this;
		}
		Vector4 &operator /=(const TYPE aRight)
		{
			x /= aRight;
			y /= aRight;
			z /= aRight;
			w /= aRight;
			return *this;
		}

		TYPE Length(void) const
		{
			return static_cast<TYPE>(sqrt(x * x + y * y + z * z + w * w));
		}
		TYPE Length2(void) const
		{
			TYPE length = Length();
			return length * length;
		}
		TYPE Dot(const Vector4 &aRight) const
		{
			return x * aRight.x + y * aRight.y + z * aRight.z + w * aRight.w;
		}
		Vector4 GetNormalized(void) const
		{
			return *this / Length();
		}

		Vector4 &Normalize(void)
		{
			*this = GetNormalized();
			return *this;
		}

		template <typename TNewType>
		Vector4<TNewType> As() const
		{
			return Vector4<TNewType>(static_cast<TNewType>(x), static_cast<TNewType>(y), static_cast<TNewType>(z), , static_cast<TNewType>(w));
		}

		TYPE x,
			y,
			z,
			w;

		static Vector4 Normalize(Vector4 aVector)
		{
			return aVector.GetNormalized();
		}
		static TYPE Dot(const Vector4 &aFirstVector, const Vector4 &aSecondVector)
		{
			return aFirstVector.Dot(aSecondVector);
		}

		operator Vector3<TYPE>() const
		{
			return Vector3<TYPE>(x, y, z);
		}

		static const Vector4 Zero,
			UnitX,
			UnitY,
			UnitZ,
			UnitW,
			One;
	};

	using Vector4c = Vector4 < char >;
	using Vector4i = Vector4 < int >;
	using Vector4ui = Vector4 < unsigned int >;
	using Vector4f = Vector4 < float >;
	using Vector4d = Vector4 < double >;

	template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::Zero(0, 0, 0, 0);
	template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::UnitX(1, 0, 0, 0);
	template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::UnitY(0, 1, 0, 0);
	template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::UnitZ(0, 0, 1, 0);
	template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::UnitW(0, 0, 0, 1);
	template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::One(1, 1, 1, 1);


}

