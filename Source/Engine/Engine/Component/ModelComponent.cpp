#include "stdafx.h"
#include "ModelComponent.h"
#include "Engine/Model/ModelInstance.h"

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

void ModelComponent::Construct()
{
}

void ModelComponent::Destruct()
{
}
