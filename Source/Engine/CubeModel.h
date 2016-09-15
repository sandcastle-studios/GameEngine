#pragma once
#include "Model.h"

class Texture;

class CubeModel : public Model
{
public:
	CubeModel(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<Texture> & aTexture);
	~CubeModel();
};

