#include "stdafx.h"
#include "ModelInstance.h"
#include "Model.h"
#include "ConstantBuffer.h"
#include "DXRenderer.h"
#include "ModelRenderer.h"

ModelInstance::ModelInstance(std::shared_ptr<Model> aModel)
{
	myModel = aModel;
	// myWorldMatrixCB = std::make_unique<ConstantBuffer<Matrix44f>>(Matrix44f::Identity);
}

ModelInstance::~ModelInstance()
{
}

void ModelInstance::Render() const
{
	// myWorldMatrixCB->BindToVS(1);
	Engine::GetInstance().GetRenderer().GetModelRenderer().Render(*this);
}

void ModelInstance::SetMatrix(const Matrix44f & aMatrix)
{
	myWorldMatrix = aMatrix;
	// myWorldMatrixCB->UpdateData(myWorldMatrix);
}
