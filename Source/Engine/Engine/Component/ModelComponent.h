#pragma once
#include "Engine/Component/BaseComponent.h"

class ModelInstance;

class ModelComponent : public BaseComponent
{
public:
	ModelComponent();
	~ModelComponent();

private:
	std::shared_ptr<ModelInstance> myModel;

};

