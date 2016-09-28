#pragma once
#include "Engine/Component/BaseComponent.h"

class ModelInstance;

class ModelComponent : public BaseComponent
{
public:
	ModelComponent();
	~ModelComponent();

	virtual void Update(const Time & aDeltaTime) override;

	virtual void Render() const override;

	void SetModel(std::shared_ptr<ModelInstance> aModel);

	virtual void Construct() override;

	virtual void Destruct() override;

private:
	std::shared_ptr<ModelInstance> myModel;

};

