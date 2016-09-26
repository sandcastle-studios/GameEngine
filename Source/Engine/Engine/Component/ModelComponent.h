#pragma once
#include "Engine/Component/BaseComponent.h"

class ModelInstance;

class ModelComponent : public BaseComponent
{
public:
	ModelComponent();
	~ModelComponent();

	void Lol() { int lol = 1; lol; lol; lol; }
private:
	std::shared_ptr<ModelInstance> myModel;

};

