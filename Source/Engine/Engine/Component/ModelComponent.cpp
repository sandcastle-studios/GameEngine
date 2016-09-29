#include "stdafx.h"
#include "ModelComponent.h"
#include "Engine/Model/ModelInstance.h"
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

void ModelComponent::Construct()
{
}

void ModelComponent::Destruct()
{
}
