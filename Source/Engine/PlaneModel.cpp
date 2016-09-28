#include "stdafx.h"
#include "PlaneModel.h"
#include "VertexPosColUV.h"
#include "Mesh.h"

PlaneModel::PlaneModel(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<Texture> & aTexture, int aTextureTileU, int aTextureTileV)
	: Model(aEffect)
{
	std::array<VertexPosColUV, 4> verticies;
	std::array<unsigned int, 6> indicies =
	{
		0, 1, 2,
		1, 3, 2
	};

	verticies[0].position = Vector4f(-0.5f, 0.f, 0.5f, 1.f);
	verticies[0].color = Vector4f(1.f, 1.f, 1.f, 1.f);
	verticies[0].uv = Vector2f(0.f, 0.f);

	verticies[1].position = Vector4f(0.5f, 0.f, 0.5f, 1.f);
	verticies[1].color = Vector4f(1.f, 1.f, 1.f, 1.f);
	verticies[1].uv = Vector2f(static_cast<float>(aTextureTileU), 0.f);

	verticies[2].position = Vector4f(-0.5f, 0.f, -0.5f, 1.f);
	verticies[2].color = Vector4f(1.f, 1.f, 1.f, 1.f);
	verticies[2].uv = Vector2f(0.f, static_cast<float>(aTextureTileV));

	verticies[3].position = Vector4f(0.5f, 0.f, -0.5f, 1.f);
	verticies[3].color = Vector4f(1.f, 1.f, 1.f, 1.f);
	verticies[3].uv = Vector2f(static_cast<float>(aTextureTileU), static_cast<float>(aTextureTileV));

	AddMesh(std::make_shared<Mesh<VertexPosColUV>>(aTexture, verticies, indicies));
}

PlaneModel::~PlaneModel()
{
}
