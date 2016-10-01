#include "stdafx.h"
#include "ModelComponent.h"
#include "Engine/Model/ModelInstance.h"
#include "Engine/Effect/Effect.h"
#include "Engine\Model\AssimpModel.h"
#include "Engine/GameObject/GameObject.h"

namespace ENGINE_NAMESPACE
{
	ModelComponent::ModelComponent()
	{
	}

	ModelComponent::~ModelComponent()
	{
	}

	void ModelComponent::Update(const Time & aDeltaTime)
	{
	}

	void ModelComponent::Render() const
	{
		myModel->Render(myEffect, myObject->GetTransformation() * myMatrix);
	}

	void ModelComponent::SetModel(std::shared_ptr<Model> aModel)
	{
		myModel = aModel;
	}

	void ModelComponent::SetModel(const char* aModelFilePath)
	{
		std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(aModelFilePath);
		myModel = model;
	}

	const BoundingBoxf & ModelComponent::GetBoundingBox() const
	{
		return myModel->GetBoundingBox();
	}

	void ModelComponent::Construct()
	{
	}

	void ModelComponent::Destruct()
	{
	}

	void ModelComponent::SetMatrix(const Matrix44f & aMatrix)
	{
		myMatrix = aMatrix;
	}

	void ModelComponent::SetEffect(const std::shared_ptr<Effect> & aEffect)
	{
		myEffect = aEffect;
	}

	const std::shared_ptr<Effect> & ModelComponent::GetEffect() const
	{
		return myEffect;
	}
}
