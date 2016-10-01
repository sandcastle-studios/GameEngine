#include "stdafx.h"
#include "SplashScreenEffect.h"

namespace ENGINE_NAMESPACE
{
	SplashScreenEffect::SplashScreenEffect()
		: SpriteEffect("shaders/sprite/splashscreen.fx", "VShader", "shaders/sprite/splashscreen.fx", "PShader")
	{
	}

	SplashScreenEffect::~SplashScreenEffect()
	{
	}
}
