#pragma once
#include "Model.h"
#include "VertexPosColUV.h"

template<typename T>
class VertexBuffer;
class IndexBuffer;
struct VertexPosColUV;

class CubeModel : public Model<VertexPosColUV>
{
public:
	CubeModel(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture);
	~CubeModel();
};

