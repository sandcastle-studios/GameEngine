#pragma once
#include "Model.h"

class Texture;

class Skybox : public Model
{
public:
	Skybox(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<Texture> & aTexture);
	~Skybox();
};

