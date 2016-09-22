#include "stdafx.h"
#include "ModelInstance.h"
#include "Model.h"
#include "..\Buffer\ConstantBuffer.h"
#include "..\Rendering\DXRenderer.h"
#include "..\Rendering\ModelRenderer.h"

ModelInstance::ModelInstance(const std::shared_ptr<Model> & aModel)
{
	myModel = aModel;
}

ModelInstance::~ModelInstance()
{
}

void ModelInstance::Render() const
{
	myModel->Render(myWorldMatrix);
}

void ModelInstance::InstantRender() const
{
	myModel->InstantRender(myWorldMatrix);
}

void ModelInstance::SetMatrix(const Matrix44f & aMatrix)
{
	myWorldMatrix = aMatrix;
}

BoundingBoxf ModelInstance::GetBoundingBox() const
{
	BoundingBoxf boundingBox = myModel->GetBoundingBox();
	boundingBox.min = Vector4f(boundingBox.min, 1.f) * myWorldMatrix;
	boundingBox.max = Vector4f(boundingBox.max, 1.f) * myWorldMatrix;
	return boundingBox;
}
