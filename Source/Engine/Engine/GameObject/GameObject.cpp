#include "stdafx.h"
#include "Engine\GameObject\GameObject.h"

GameObject::GameObject()
{
	myScale = Vector3f::One;

	myComponents.Resize(UniqeIdentifier<BaseComponent>::nextTypeIndex);
}

GameObject::~GameObject()
{
}

void GameObject::SetPosition(const Vector3f & aPosition)
{
	myPosition = aPosition;
}

void GameObject::SetRotation(const Quaternion & aRotation)
{
	myRotation = aRotation;
	myRotation.Normalize();
}

void GameObject::SetScale(const Vector3f & aScale)
{
	myScale = aScale;
}

const Vector3f & GameObject::GetPosition() const
{
	return myPosition;
}

const Quaternion & GameObject::GetRotation() const
{
	return myRotation;
}

const Vector3f & GameObject::GetScale() const
{
	return myScale;
}

Matrix44f GameObject::GetTransformation() const
{
	Matrix44f aRotation = myRotation.GenerateMatrix();
	return aRotation * Matrix44f::CreateScale(myScale.x, myScale.y, myScale.z) * Matrix44f::CreateTranslation(myPosition);
}
