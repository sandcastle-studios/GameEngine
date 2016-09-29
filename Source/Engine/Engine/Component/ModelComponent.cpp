#include "stdafx.h"
#include "ModelComponent.h"
#include "Engine/Model/ModelInstance.h"
#include "Engine/Effect/Effect.h"
#include "Engine\Model\AssimpModel.h"

#include "Engine/GameObject/GameObject.h"

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
	myModel->Render(myObject->GetTransformation());
}

void ModelComponent::SetModel(std::shared_ptr<Model> aModel)
{
	myModel = aModel;
}

void ModelComponent::SetModel(const char* aModelFilePath, std::shared_ptr<Effect> aEffect)
{
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(aEffect, aModelFilePath);
	std::shared_ptr<ModelInstance> modelInstance = std::make_shared<ModelInstance>(model);
	myModel = modelInstance;
}

void ModelComponent::Construct()
{
}

void ModelComponent::Destruct()
{
}
