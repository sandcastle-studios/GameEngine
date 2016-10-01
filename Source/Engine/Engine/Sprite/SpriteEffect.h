#pragma once
#include "Engine/Effect/Effect.h"

namespace ENGINE_NAMESPACE
{
	class SpriteEffect : public Effect
	{
	public:
		SpriteEffect();
		SpriteEffect(const char * aVertexFile, const char * aVertexEntryPoint,
			const char * aPixelFile, const char * aPixelEntryPoint);
		~SpriteEffect();
	};
}
