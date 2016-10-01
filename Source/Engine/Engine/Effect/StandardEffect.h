#pragma once
#include "Engine\Effect\Effect.h"

namespace ENGINE_NAMESPACE
{
	class StandardEffect : public Effect
	{
	public:
		StandardEffect(const char * aVertexPath = "shaders/pbr/vertex.fx", const char * aVertexEntryPoint = "VShader", const char * aPixelPath = "shaders/pbr/pixel.fx", const char * aPixelEntryPoint = "PShader");
		~StandardEffect();
	};
}
