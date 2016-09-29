#pragma once
#include "Engine/Component/BaseComponent.h"

class Model;
class Effect;

class ModelComponent : public BaseComponent
{
public:
	ModelComponent();
	~ModelComponent();

	virtual void Update(const Time & aDeltaTime) override;

	virtual void Render() const override;

	void SetModel(std::shared_ptr<Model> aModel);

	void SetModel(const char* aModelFilePath, std::shared_ptr<Effect> aEffect);

	virtual void Construct() override;

	virtual void Destruct() override;

private:
	std::shared_ptr<Model> myModel;
};

