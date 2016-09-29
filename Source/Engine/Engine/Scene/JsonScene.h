#pragma once
#include "Engine\Scene\Scene.h"


class JsonScene : public Scene
{
public:
	JsonScene(const char* aFilePath = "");
	~JsonScene();

	virtual void Update(const Time & aDeltaTime) override;
	virtual void Render() override;

private:
};

