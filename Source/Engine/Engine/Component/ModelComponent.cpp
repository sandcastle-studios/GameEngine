#include "stdafx.h"
#include "ModelComponent.h"
#include "Engine/Model/ModelInstance.h"
#include "Engine/Effect/Effect.h"
#include "Engine\Model\AssimpModel.h"


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
	myModel->Render();
}

void ModelComponent::SetModel(std::shared_ptr<ModelInstance> aModel)
{
	myModel = aModel;
}

void ModelComponent::SetModel(const char* aModelFilePath, std::shared_ptr<Effect> aEffect)
{
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(aEffect, aModelFilePath);
}

void ModelComponent::Construct()
{
}

void ModelComponent::Destruct()
{
}
