#include "stdafx.h"
#include "Engine\GameObject\GameObject.h"

GameObject::GameObject()
{
	myComponents.Resize(UniqeIdentifier<BaseComponent>::nextTypeIndex);
}

GameObject::~GameObject()
{
}

const Vector3f & GameObject::GetPosition() const
{
	return myPosition;
}

const Quaternion & GameObject::GetRotation() const
{
	return myRotation;
}

Matrix44f GameObject::GetTransformation() const
{
	Matrix44f tempTransformation = myRotation.GenerateMatrix();
	tempTransformation.SetPosition(myPosition);
	return tempTransformation;
}
