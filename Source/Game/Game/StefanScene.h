#pragma once
#include <Engine/Scene/Scene.h>

class StefanScene : public Scene
{
public:
	StefanScene();
	~StefanScene();

	virtual void Update(const Time & aDeltaTime) override;
	virtual void Render() override;

private:
	void CreateFactories();


};

