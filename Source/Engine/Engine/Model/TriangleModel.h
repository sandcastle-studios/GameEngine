#pragma once
#include "Engine\Model\Model.h"

class Texture;

class TriangleModel : public Model
{
public:
	TriangleModel(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture);
	~TriangleModel();
};
