#pragma once
#include "Engine\Scene\Scene.h"

template<typename T>
class ConstantBuffer;
class SplashScreenEffect;

struct SplashScreenCBuffer
{
	Vector4f time;
};

class SplashScreenScene : public Scene
{
public:
	SplashScreenScene();
	~SplashScreenScene();

	void Update(const Time & aDeltaTime) override;
	void Render() override;

private:
	std::unique_ptr<ConstantBuffer<SplashScreenCBuffer>> myConstantBuffer;
	std::shared_ptr<SplashScreenEffect> mySplashScreenEffect;
	Sprite mySprite;
};

