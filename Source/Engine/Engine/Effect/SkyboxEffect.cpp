#include "stdafx.h"
#include "SkyboxEffect.h"

namespace ENGINE_NAMESPACE
{
	SkyboxEffect::SkyboxEffect()
		: StandardEffect("shaders/pbr/vertex.fx", "VShader", "shaders/pbr/skybox.fx", "PShader")
	{
	}


	SkyboxEffect::~SkyboxEffect()
	{
	}
}
