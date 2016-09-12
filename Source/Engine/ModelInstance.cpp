#include "stdafx.h"
#include "ModelInstance.h"
#include "Model.h"
#include "ConstantBuffer.h"

ModelInstance::ModelInstance(std::shared_ptr<GenericModel> aModel)
{
	myModel = aModel;
	myWorldMatrixCB = std::make_unique<ConstantBuffer<Matrix44f>>(Matrix44f::Identity);
}

ModelInstance::~ModelInstance()
{
}

void ModelInstance::Render()
{
	myWorldMatrixCB->BindToVS(1);
	myModel->Render();
}

void ModelInstance::SetMatrix(const Matrix44f & aMatrix)
{
	myWorldMatrix = aMatrix;
	myWorldMatrixCB->UpdateData(myWorldMatrix);
}

const Matrix44f & ModelInstance::GetMatrix()
{
	return myWorldMatrix;
}

Vector3f ModelInstance::GetPosition() const
{
	return myWorldMatrix.GetPosition();
}

std::shared_ptr<GenericModel> ModelInstance::GetModel()
{
	return myModel;
}
