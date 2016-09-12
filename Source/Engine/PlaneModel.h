#pragma once
#include "Model.h"

struct VertexPosColUV;

class PlaneModel : public Model<VertexPosColUV>
{
public:
	PlaneModel(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture, int aTextureTileU = 1, int aTextureTileV = 1);
	~PlaneModel();
};

