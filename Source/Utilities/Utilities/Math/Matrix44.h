#pragma once

// Forward declarations
//
template<typename TYPE>
class Matrix33;

template<typename TYPE>
class Matrix44
{
public:     // Constant to avoid using magic numbers
			//
	static const unsigned int   NumRows = 4,
		NumColumns = 4,
		NumElements = NumRows * NumColumns;

	// Initializes the matrix to the identity matrix
	//
	Matrix44()
	{
		for (unsigned int y = 0; y < NumRows; y++)
		{
			for (unsigned int x = 0; x < NumColumns; x++)
			{
				Read(y, x) = static_cast<TYPE>(x == y ? 1 : 0);
			}
		}
	}

	// Initializes the matrix with the data from anOther
	//
	Matrix44(const Matrix44 &anOther)
	{
		myMatrix = anOther.myMatrix;
	}

	// Initializes the matrix with the static_cast'ed data from anOther
	//
	template<typename U>
	Matrix44(const Matrix44<U> &anOther)
	{
		for (unsigned int y = 0; y < NumRows; y++)
		{
			for (unsigned int x = 0; x < NumColumns; x++)
			{
				Read(y, x) = static_cast<U>(anOther.Read(y, x));
			}
		}
	}

	// Initializes the matrix with the data from an array
	//
	Matrix44(const TYPE(&anArray)[NumElements])
	{
		for (int i = 0; i < NumElements; i++)
		{
			myMatrix[i] = anArray[i];
		}
	}

	// Initializes the matrix with plain values
	//
	Matrix44(
		const TYPE a11, const TYPE a12, const TYPE a13, const TYPE a14,
		const TYPE a21, const TYPE a22, const TYPE a23, const TYPE a24,
		const TYPE a31, const TYPE a32, const TYPE a33, const TYPE a34,
		const TYPE a41, const TYPE a42, const TYPE a43, const TYPE a44)
	{
		myMatrix[0] = a11;
		myMatrix[1] = a12;
		myMatrix[2] = a13;
		myMatrix[3] = a14;


		myMatrix[4] = a21;
		myMatrix[5] = a22;
		myMatrix[6] = a23;
		myMatrix[7] = a24;

		myMatrix[8] = a31;
		myMatrix[9] = a32;
		myMatrix[10] = a33;
		myMatrix[11] = a34;

		myMatrix[12] = a41;
		myMatrix[13] = a42;
		myMatrix[14] = a43;
		myMatrix[15] = a44;
	}

	// Adds and assigns the values of aRight to this matrix
	//
	Matrix44 &operator +=(const Matrix44 &aRight)
	{
		for (int i = 0; i < NumElements; i++)
		{
			myMatrix[i] += aRight.myMatrix[i];
		}
		return *this;
	}

	// Subtract and assigns the values of aRight to this matrix
	//
	Matrix44 &operator -=(const Matrix44 &aRight)
	{
		for (int i = 0; i < NumElements; i++)
		{
			myMatrix[i] -= aRight.myMatrix[i];
		}
		return *this;
	}

	// Multiplies this matrix with aRight
	//
	Matrix44 &operator *=(const Matrix44 &aRight)
	{
		*this = *this * aRight;
		return *this;
	}

	// Sets the values of this matrix to those of aRight
	//
	Matrix44 &operator =(const Matrix44 &aRight)
	{
		myMatrix = aRight.myMatrix;
		return *this;
	}

	// Returns a transposed copy of this matrix
	//
	Matrix44 &Transpose()
	{
		Matrix44 copy = *this;
		for (int y = 0; y < NumRows; y++)
		{
			for (int x = 0; x < NumColumns; x++)
			{
				Read(y, x) = copy.Read(x, y);
			}
		}
		return *this;
	}

	Matrix44 GetInverse() const
	{
		Matrix44 inverse = *this;
		inverse.SetPosition(Vector3f::Zero);
		inverse.Transpose();
		Vector4<TYPE> position = Vector4<TYPE>(-GetPosition(), 1.f);
		position = position * inverse;
		inverse.SetPosition(position);
		return inverse;
	}

	static Matrix44 CreateTranslation(const Vector3f &aPoint)
	{
		return Matrix44(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			aPoint.x, aPoint.y, aPoint.z, 1
		);
	}

	static Matrix44 CreateTranslation(const TYPE x, const TYPE y, const TYPE z)
	{
		return Matrix44(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			x, y, z, 1
		);
	}

	static Matrix44 CreateScale(const TYPE x, const TYPE y, const TYPE z)
	{
		return Matrix44(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		);
	}

	static Matrix44 CreateProjection(float aFovInDegrees, float aProjectionWidth, float aProjectionHeight, float aNearPlane, float aFarPlane)
	{
		TYPE fov = aFovInDegrees / 180.f * Pi;
		TYPE height = cosf(fov / 2.f) / sinf(fov / 2.f);
		TYPE aspectRatio = aProjectionWidth / aProjectionHeight;
		const TYPE scaling = aFarPlane / (aFarPlane - aNearPlane);
			
		return Matrix44(height / aspectRatio, 0.f, 0.f, 0.f,
			0.f, height, 0.f, 0.f,
			0.f, 0.f, scaling, 1.f,
			0.f, 0.f, -scaling * aNearPlane, 0.f);
	}

	// Creates a transformation matrix for rotating anAngle rad around the x-axis
	//
	static Matrix44 CreateRotateAroundX(const TYPE anAngle);

	// Creates a transformation matrix for rotating anAngle rad around the y-axis
	//
	static Matrix44 CreateRotateAroundY(const TYPE anAngle);

	// Creates a transformation matrix for rotating anAngle rad around the z-axis
	//
	static Matrix44 CreateRotateAroundZ(const TYPE anAngle);

	// Returns a transposed copy of aMatrix
	//
	static Matrix44 Transpose(Matrix44 aMatrix)
	{
		return aMatrix.Transpose();
	}

	// The data of this matrix
	//
#pragma warning( disable : 4201 ) // NOTE: This works fine in VC2013 and GCC so I'm keeping it. //MAHAM
	union
	{
		struct
		{
			TYPE    m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44;
		};

		std::array<TYPE, NumElements> myMatrix;
	};

	// Pre-created identity matrix
	//
	static const Matrix44   Identity,
		Zero;

	__forceinline TYPE &Read(const int aRow, const int aColumn)
	{
		return myMatrix[aRow * NumColumns + aColumn];
	}
	__forceinline TYPE Read(const int aRow, const int aColumn) const
	{
		return myMatrix[aRow * NumColumns + aColumn];
	}

	inline void SetPosition(Vector3f aPosition)
	{
		m41 = aPosition.x;
		m42 = aPosition.y;
		m43 = aPosition.z;
	}

	inline Vector3f GetPosition() const
	{
		return Vector3f(m41, m42, m43);
	}

	bool Inverse()
	{
		// From http://stackoverflow.com/a/1148405
		
		float * m = &myMatrix[0];

		float inv[16], det;
		float invOut[16];
		int i;

		inv[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (det == 0.f)
			return false;

		det = 1.f / det;

		for (i = 0; i < 16; i++)
			invOut[i] = inv[i] * det;

		memcpy(&myMatrix[0], invOut, sizeof(invOut));

		return true;
	}
};

template <typename TYPE>
const Matrix44<TYPE> Matrix44<TYPE>::Zero(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
template <typename TYPE>
const Matrix44<TYPE> Matrix44<TYPE>::Identity;
	
template <typename TYPE>
Matrix44<TYPE> Matrix44<TYPE>::CreateRotateAroundX(const TYPE anAngle)
{
	TYPE sin = static_cast<TYPE>(std::sin(anAngle));
	TYPE cos = static_cast<TYPE>(std::cos(anAngle));
	return Matrix44(1, 0, 0, 0,
		0, cos, sin, 0,
		0, -sin, cos, 0,
		0, 0, 0, 1);
}

template <typename TYPE>
Matrix44<TYPE> Matrix44<TYPE>::CreateRotateAroundY(const TYPE anAngle)
{
	TYPE sin = static_cast<TYPE>(std::sin(anAngle));
	TYPE cos = static_cast<TYPE>(std::cos(anAngle));
	return Matrix44(cos, 0, -sin, 0,
		0, 1, 0, 0,
		sin, 0, cos, 0,
		0, 0, 0, 1);
}

template <typename TYPE>
Matrix44<TYPE> Matrix44<TYPE>::CreateRotateAroundZ(const TYPE anAngle)
{
	TYPE sin = static_cast<TYPE>(std::sin(anAngle));
	TYPE cos = static_cast<TYPE>(std::cos(anAngle));
	return Matrix44(cos, sin, 0, 0,
		-sin, cos, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

using Matrix44f = Matrix44 < float >;

// Returns a new matrix which is the sum of aLeft and aRight
//
template<typename TYPE>
Matrix44<TYPE> operator +(Matrix44<TYPE> aLeft, const Matrix44<TYPE> &aRight)
{
	return aLeft += aRight;
}

// Returns a new matrix wich is the difference of aLeft and aRight
//
template<typename TYPE>
Matrix44<TYPE> operator -(Matrix44<TYPE> aLeft, const Matrix44<TYPE> &aRight)
{
	return aLeft -= aRight;
}

// Returns a new matrix which is the product of aLeft and aRight
//
template<typename TYPE>
Matrix44<TYPE> operator *(const Matrix44<TYPE> &aLeft, const Matrix44<TYPE> &aRight)
{
	Matrix44<TYPE> newMatrix;
	const unsigned int numRows = 4;
	const unsigned int numColumns = 4;
	for (unsigned int i = 0; i < numRows; i++)
	{
		for (unsigned int j = 0; j < numColumns; j++)
		{
			newMatrix.Read(i, j) = static_cast<TYPE>(0);
			for (unsigned int k = 0; k < 4; k++)
			{
				newMatrix.Read(i, j) += aLeft.Read(i, k) * aRight.Read(k, j);
			}
		}
	}
	return newMatrix;
}

// Returns a new matrix which is the product of the vector aLeft and the matrix aRight
//
template<typename TYPE>
Vector4<TYPE> operator *(Vector4<TYPE> aLeft, const Matrix44<TYPE> &aRight)
{
	Vector4<TYPE> out;
	out.x = (aRight.m11 * aLeft.x) + (aRight.m21 * aLeft.y) + (aRight.m31 * aLeft.z) + (aRight.m41 * aLeft.w);
	out.y = (aRight.m12 * aLeft.x) + (aRight.m22 * aLeft.y) + (aRight.m32 * aLeft.z) + (aRight.m42 * aLeft.w);
	out.z = (aRight.m13 * aLeft.x) + (aRight.m23 * aLeft.y) + (aRight.m33 * aLeft.z) + (aRight.m43 * aLeft.w);
	out.w = (aRight.m14 * aLeft.x) + (aRight.m24 * aLeft.y) + (aRight.m34 * aLeft.z) + (aRight.m44 * aLeft.w);
	return out;
}

// Compares aLeft and aRight componentwise
//
template<typename TYPE>
bool operator ==(const Matrix44<TYPE> &aLeft, const Matrix44<TYPE> &aRight)
{
	return aLeft.myMatrix == aRight.myMatrix;
}

// Returns the negated result of aLeft == aRight
//
template<typename TYPE>
bool operator !=(const Matrix44<TYPE> &aLeft, const Matrix44<TYPE> &aRight)
{
	return (aLeft == aRight) == false;
}
