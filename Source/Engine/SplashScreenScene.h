#pragma once
#include "Scene.h"

template<typename T>
class ConstantBuffer;
class Texture;
class Effect;

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
	std::shared_ptr<Texture> myTexture;
	std::shared_ptr<Effect> mySplashScreenEffect;
};

