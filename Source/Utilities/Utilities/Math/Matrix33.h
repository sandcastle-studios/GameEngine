#pragma once

namespace ENGINE_NAMESPACE
{

	template<typename TYPE>
	class Matrix33
	{
	public:

		TYPE
			m11, m12,
			m21, m22,
			m31, m32;

		Matrix33()
		{
			m11 = 1; m12 = 0;
			m21 = 0; m22 = 1;
			m31 = 0; m32 = 0;
		}

		// Initializes the matrix with plain values
		//
		Matrix33(
			const TYPE a11, const TYPE a12,
			const TYPE a21, const TYPE a22,
			const TYPE a31, const TYPE a32)
		{
			m11 = a11;
			m12 = a12;

			m21 = a21;
			m22 = a22;

			m31 = a31;
			m32 = a32;
		}

		Matrix33<TYPE> GetInverse() const
		{
			const float det =
				m11 * (m22)-
				m12 * (m21);

			const float invdet = 1.f / det;

			Matrix33 minv;

			minv.m11 = (m22)* invdet;
			minv.m12 = (-m12) * invdet;
			minv.m21 = (-m21) * invdet;
			minv.m22 = (m11)* invdet;
			minv.m31 = (m21 * m32 - m31 * m22) * invdet;
			minv.m32 = (m31 * m12 - m11 * m32) * invdet;

			return minv;
		}

		Matrix33 &Rotate2D(const TYPE anAngle)
		{
			*this *= CreateRotateAroundZ(anAngle);
			return *this;
		}

		Matrix33 &SetRotation2D(const TYPE anAngle)
		{
			TYPE sin = static_cast<TYPE>(std::sin(anAngle));
			TYPE cos = static_cast<TYPE>(std::cos(anAngle));
			m11 = cos;
			m12 = sin;
			m21 = -sin;
			m22 = cos;
			return *this;
		}

		Matrix33 &SetPosition(const Vector2<TYPE> &aPosition)
		{
			m31 = aPosition.x;
			m32 = aPosition.y;
			return *this;
		}

		Vector2<TYPE> &GetPosition()
		{
			return Vector2<TYPE>(m31, m32);
		}

		// Multiplies this matrix with aRight
		//
		Matrix33 &operator *=(const Matrix33 &aRight)
		{
			*this = *this * aRight;
			return *this;
		}

		static Matrix33 CreateTranslation(const TYPE aX, const TYPE aY)
		{
			return Matrix33(
				1, 0,
				0, 1,
				aX, aY);
		}
		static Matrix33 CreateTranslation(const Vector2f aPosition)
		{
			return Matrix33(
				1, 0,
				0, 1,
				aPosition.x, aPosition.y);
		}

		static Matrix33 CreateScale(const TYPE aX, const TYPE aY)
		{
			return Matrix33(
				aX, 0,
				0, aY,
				0, 0);
		}

		// Creates a transformation matrix for rotating anAngle rad around the z-axis
		//
		static Matrix33 CreateRotateAroundZ(const TYPE anAngle)
		{
			TYPE sin = static_cast<TYPE>(std::sin(anAngle));
			TYPE cos = static_cast<TYPE>(std::cos(anAngle));
			return Matrix33(cos, sin,
				-sin, cos,
				0, 0);
		}

		// Pre-created matrices
		//
		static const Matrix33   Identity,   // Identity matrix
			Zero;       // Matrix with all 0
	};

	template <typename TYPE>
	const Matrix33<TYPE> Matrix33<TYPE>::Zero(0, 0, 0, 0, 0, 0, 0, 0, 0);
	template <typename TYPE>
	const Matrix33<TYPE> Matrix33<TYPE>::Identity;

	// Alias for Matrix33<float>. Add more if needed.
	//
	using Matrix33f = Matrix33 < float >;

	// Returns a new matrix which is the sum of aLeft and aRight
	//
	template<typename TYPE>
	Matrix33<TYPE> operator +(Matrix33<TYPE> aLeft, const Matrix33<TYPE> &aRight)
	{
		return aLeft += aRight;
	}

	// Returns a new matrix wich is the difference of aLeft and aRight
	//
	template<typename TYPE>
	Matrix33<TYPE> operator -(Matrix33<TYPE> aLeft, const Matrix33<TYPE> &aRight)
	{
		return aLeft -= aRight;
	}

	// Returns a new matrix which is the product of aLeft and aRight
	//
	template<typename TYPE>
	Matrix33<TYPE> operator *(const Matrix33<TYPE> &aLeft, const Matrix33<TYPE> &aRight)
	{
		Matrix33<TYPE> n;

		n.m11 = (aLeft.m11 * aRight.m11) + (aLeft.m12 * aRight.m21);
		n.m12 = (aLeft.m11 * aRight.m12) + (aLeft.m12 * aRight.m22);

		n.m21 = (aLeft.m21 * aRight.m11) + (aLeft.m22 * aRight.m21);
		n.m22 = (aLeft.m21 * aRight.m12) + (aLeft.m22 * aRight.m22);

		n.m31 = (aLeft.m31 * aRight.m11) + (aLeft.m32 * aRight.m21) + aRight.m31;
		n.m32 = (aLeft.m31 * aRight.m12) + (aLeft.m32 * aRight.m22) + aRight.m32;

		return n;
	}

	// Returns a new matrix which is the product of the vector aLeft and the matrix aRight
	//
	template<typename TYPE>
	Vector2<TYPE> operator *(Vector2<TYPE> aLeft, const Matrix33<TYPE> &aRight)
	{
		Vector2<TYPE> out;
		out.x = (aRight.m11 * aLeft.x) + (aRight.m21 * aLeft.y) + aRight.m31;
		out.y = (aRight.m12 * aLeft.x) + (aRight.m22 * aLeft.y) + aRight.m32;
		return out;
	}

	// Returns a new matrix which is the product of the vector aLeft and the matrix aRight
	//
	template<typename TYPE>
	Vector3<TYPE> operator *(Vector3<TYPE> aLeft, const Matrix33<TYPE> &aRight)
	{
		Vector3<TYPE> out;
		out.x = (aRight.m11 * aLeft.x) + (aRight.m21 * aLeft.y) + (aRight.m31 * aLeft.z);
		out.y = (aRight.m12 * aLeft.x) + (aRight.m22 * aLeft.y) + (aRight.m32 * aLeft.z);
		out.z = aLeft.z;
		return out;
	}

	// Compares aLeft and aRight componentwise
	//
	template<typename TYPE>
	bool operator ==(const Matrix33<TYPE> &aLeft, const Matrix33<TYPE> &aRight)
	{
		return aLeft.myMatrix == aRight.myMatrix;
	}

	// Returns the negated result of aLeft == aRight
	//
	template<typename TYPE>
	bool operator !=(const Matrix33<TYPE> &aLeft, const Matrix33<TYPE> &aRight)
	{
		return (aLeft == aRight) == false;
	}

}
