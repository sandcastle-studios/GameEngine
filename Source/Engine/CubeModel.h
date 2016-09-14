#pragma once
#include "Model.h"

class Texture;

class CubeModel : public Model
{
public:
	CubeModel(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture);
	~CubeModel();
};

