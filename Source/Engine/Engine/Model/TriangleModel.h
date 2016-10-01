#pragma once
#include "Engine\Model\Model.h"

namespace ENGINE_NAMESPACE
{
	class Texture;

	class TriangleModel : public Model
	{
	public:
		TriangleModel(std::shared_ptr<Texture> aTexture);
		~TriangleModel();
	};
}
