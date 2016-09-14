#pragma once

template<typename T>
struct BoundingBox
{
public:
	BoundingBox();
	BoundingBox(const Vector3<T> & aInitialPosition);

	void SetToPosition(const Vector3<T> & aPosition);

	void ExpandToContain(const BoundingBox & aBoundingBox);
	void ExpandToContain(const Vector3<T> & aPosition);

	Vector3<T> GetSize() const;
	T GetMaximumRadius() const;
	Vector3<T> GetCenter() const;

	Vector3<T> min,
		max;
};

template<typename T>
inline BoundingBox<T>::BoundingBox()
{
}

template<typename T>
inline BoundingBox<T>::BoundingBox(const Vector3<T> & aInitialPosition)
{
	SetToPosition(aInitialPosition);
}

template<typename T>
inline void BoundingBox<T>::SetToPosition(const Vector3<T> & aPosition)
{
	min = aPosition;
	max = aPosition;
}

template<typename T>
inline Vector3<T> BoundingBox<T>::GetSize() const
{
	return max - min;
}

template<typename T>
inline Vector3<T> BoundingBox<T>::GetCenter() const
{
	return (min + max) / static_cast<T>(2);
}

template<typename T>
inline void BoundingBox<T>::ExpandToContain(const BoundingBox & aBoundingBox)
{
	ExpandToContain(aBoundingBox.min + aBoundingBox.GetSize() * Vector3f(0.f, 0.f, 0.f));
	ExpandToContain(aBoundingBox.min + aBoundingBox.GetSize() * Vector3f(1.f, 0.f, 0.f));
	ExpandToContain(aBoundingBox.min + aBoundingBox.GetSize() * Vector3f(0.f, 1.f, 0.f));
	ExpandToContain(aBoundingBox.min + aBoundingBox.GetSize() * Vector3f(1.f, 1.f, 0.f));

	ExpandToContain(aBoundingBox.min + aBoundingBox.GetSize() * Vector3f(0.f, 0.f, 1.f));
	ExpandToContain(aBoundingBox.min + aBoundingBox.GetSize() * Vector3f(1.f, 0.f, 1.f));
	ExpandToContain(aBoundingBox.min + aBoundingBox.GetSize() * Vector3f(0.f, 1.f, 1.f));
	ExpandToContain(aBoundingBox.min + aBoundingBox.GetSize() * Vector3f(1.f, 1.f, 1.f));
}

template<typename T>
inline void BoundingBox<T>::ExpandToContain(const Vector3<T> & aPosition)
{
	if (aPosition.x < min.x)
		min.x = aPosition.x;
	if (aPosition.y < min.y)
		min.y = aPosition.y;
	if (aPosition.z < min.z)
		min.z = aPosition.z;

	if (aPosition.x > max.x)
		max.x = aPosition.x;
	if (aPosition.y > max.y)
		max.y = aPosition.y;
	if (aPosition.z > max.z)
		max.z = aPosition.z;
}

template<typename T>
inline T BoundingBox<T>::GetMaximumRadius() const
{
	return std::sqrt(GetSize().x * GetSize().x + GetSize().y * GetSize().y + GetSize().z * GetSize().z);
}

using BoundingBoxf = BoundingBox<float>;
using BoundingBoxi = BoundingBox<int>;
using BoundingBoxui = BoundingBox<unsigned int>;
