#pragma once
#include "Engine\Model\Model.h"

namespace ENGINE_NAMESPACE
{
	class Texture;

	class Skybox : public Model
	{
	public:
		Skybox(const std::shared_ptr<Texture> & aTexture);
		~Skybox();
	};
}
