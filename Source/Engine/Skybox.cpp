#include "stdafx.h"
#include "Skybox.h"
#include "VertexPosColUV.h"

Skybox::Skybox(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture)
	: Model(aEffect, aTexture)
{
	Vector2f quadSize = Vector2f(0.25f, 0.25f);
	std::array<VertexPosColUV, 36> verticies;
	memset(&verticies[0], 0, verticies.size() * sizeof(VertexPosColUV));

	for (size_t i = 0; i < verticies.size(); i++)
	{
		verticies[i].color = Vector4f(1.f, 1.f, 1.f, 1.f);
	}

	Matrix44f m = Matrix44f::Identity;

	for (size_t i = 0; i < 4; i++)
	{
		verticies[i * 6 + 0].position = Vector4f(-.5f, .5f, -.5f, 1.f) * m;
		verticies[i * 6 + 0].uv = quadSize * Vector2f(static_cast<float>(i), 1.f);

		verticies[i * 6 + 1].position = Vector4f(-.5f, .5f, .5f, 1.f) * m;
		verticies[i * 6 + 1].uv = quadSize * Vector2f(static_cast<float>(i) + 1.f, 1.f);

		verticies[i * 6 + 2].position = Vector4f(-.5f, -.5f, -.5f, 1.f) * m;
		verticies[i * 6 + 2].uv = quadSize * Vector2f(static_cast<float>(i), 2.f);

		verticies[i * 6 + 3].position = Vector4f(-.5f, -.5f, .5f, 1.f) * m;
		verticies[i * 6 + 3].uv = quadSize * Vector2f(static_cast<float>(i) + 1.f, 2.f);

		verticies[i * 6 + 4].position = Vector4f(-.5f, -.5f, -.5f, 1.f) * m;
		verticies[i * 6 + 4].uv = quadSize * Vector2f(static_cast<float>(i), 2.f);

		verticies[i * 6 + 5].position = Vector4f(-.5f, .5f, .5f, 1.f) * m;
		verticies[i * 6 + 5].uv = quadSize * Vector2f(static_cast<float>(i) + 1.f, 1.f);

		m *= Matrix44f::CreateRotateAroundY(HalfPi);
	}

	// Bottom
	verticies[4 * 6 + 0].position = Vector4f(-0.5f, -.5f, 0.5f, 1.f) * m;
	verticies[4 * 6 + 0].uv = quadSize * Vector2f(1.f, 2.f);

	verticies[4 * 6 + 1].position = Vector4f(.5f, -.5f, .5f, 1.f) * m;
	verticies[4 * 6 + 1].uv = quadSize * Vector2f(2.f, 2.f);

	verticies[4 * 6 + 2].position = Vector4f(-.5f, -.5f, -.5f, 1.f) * m;
	verticies[4 * 6 + 2].uv = quadSize * Vector2f(1.f, 3.f);

	verticies[4 * 6 + 3].position = Vector4f(.5f, -.5f, -.5f, 1.f) * m;
	verticies[4 * 6 + 3].uv = quadSize * Vector2f(2.f, 3.f);

	verticies[4 * 6 + 4].position = Vector4f(-.5f, -.5f, -.5f, 1.f) * m;
	verticies[4 * 6 + 4].uv = quadSize * Vector2f(1.f, 3.f);

	verticies[4 * 6 + 5].position = Vector4f(.5f, -.5f, .5f, 1.f) * m;
	verticies[4 * 6 + 5].uv = quadSize * Vector2f(2.f, 2.f);


	// Top
	verticies[5 * 6 + 0].position = Vector4f(-.5f, .5f, .5f, 1.f) * m;
	verticies[5 * 6 + 0].uv = quadSize * Vector2f(1.f, 1.f);

	verticies[5 * 6 + 1].position = Vector4f(-.5f, .5f, -.5f, 1.f) * m;
	verticies[5 * 6 + 1].uv = quadSize * Vector2f(1.f, 0.f);

	verticies[5 * 6 + 2].position = Vector4f(.5f, .5f, .5f, 1.f) * m;
	verticies[5 * 6 + 2].uv = quadSize * Vector2f(2.f, 1.f);

	verticies[5 * 6 + 3].position = Vector4f(.5f, .5f, -.5f, 1.f) * m;
	verticies[5 * 6 + 3].uv = quadSize * Vector2f(2.f, 0.f);

	verticies[5 * 6 + 4].position = Vector4f(.5f, .5f, .5f, 1.f) * m;
	verticies[5 * 6 + 4].uv = quadSize * Vector2f(2.f, 1.f);

	verticies[5 * 6 + 5].position = Vector4f(-.5f, .5f, -.5f, 1.f) * m;
	verticies[5 * 6 + 5].uv = quadSize * Vector2f(1.f, 0.f);
	 
	std::array<unsigned int, 36> indicies;
	for (size_t i = 0; i < indicies.size(); i++)
	{
		indicies[i] = static_cast<unsigned int>(i);
	}

	CreateModel(verticies, indicies);
}


Skybox::~Skybox()
{
}
