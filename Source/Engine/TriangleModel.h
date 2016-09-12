#pragma once
#include "Model.h"

class TriangleModel : public Model<SimpleVertex>
{
public:
	TriangleModel(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture);
	~TriangleModel();
};
