#pragma once
#include "Model.h"

struct VertexPosColUV;

class Skybox : public Model<VertexPosColUV>
{
public:
	Skybox(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture);
	~Skybox();
};

