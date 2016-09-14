#pragma once
#include "Model.h"

class Texture;

class Skybox : public Model
{
public:
	Skybox(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture);
	~Skybox();
};

