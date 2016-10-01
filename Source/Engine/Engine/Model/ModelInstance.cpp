#include "stdafx.h"
#include "Engine\Model\ModelInstance.h"
#include "Engine\Model\Model.h"
#include "Engine\Buffer\ConstantBuffer.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Rendering\ModelRenderer.h"

namespace ENGINE_NAMESPACE
{

	ModelInstance::ModelInstance(const std::shared_ptr<Model> & aModel)
	{
		myModel = aModel;
		myEffect = nullptr;
	}

	ModelInstance::~ModelInstance()
	{
	}

	void ModelInstance::SetEffect(const std::shared_ptr<Effect> & aEffect)
	{
		myEffect = aEffect;
	}

	const std::shared_ptr<Effect> & ModelInstance::GetEffect() const
	{
		return myEffect;
	}

	void ModelInstance::Render() const
	{
		myModel->Render(myEffect, myWorldMatrix);
	}

	void ModelInstance::InstantRender() const
	{
		myModel->InstantRender(myEffect, myWorldMatrix);
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
	
}
