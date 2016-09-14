#include "stdafx.h"
#include "TriangleModel.h"
#include "SimpleVertex.h"
#include "Mesh.h"

TriangleModel::TriangleModel(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture)
	: Model(aEffect)
{
	std::array<SimpleVertex, 3> vertexData;

	vertexData[0].position = Vector4f(-0.5f, -0.5f, 0.f, 1.0f);
	vertexData[0].color = Vector4f(1.0f, 0.0f, 0.0f, 1.f);

	vertexData[1].position = Vector4f(0.0f, 0.5f, 0.f, 1.0f);
	vertexData[1].color = Vector4f(0.f, 1.f, 0.f, 1.f);

	vertexData[2].position = Vector4f(0.5f, -0.5f, 0.f, 1.0f);
	vertexData[2].color = Vector4f(0.f, 0.f, 1.f, 1.f);

	std::array<unsigned int, 3> indexBuffer = { 0, 1, 2 };
	
	AddMesh(std::make_unique<Mesh<SimpleVertex>>(aTexture, vertexData, indexBuffer));
}

TriangleModel::~TriangleModel()
{
}
