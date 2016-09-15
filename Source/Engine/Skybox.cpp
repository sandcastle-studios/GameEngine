#include "stdafx.h"
#include "Skybox.h"
#include "Vertex.h"
#include "Mesh.h"

Skybox::Skybox(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<Texture> & aTexture)
	: Model(aEffect)
{
	const float skyboxSize = .5f;
	Vector2f quadSize = Vector2f(0.25f, 0.25f);
	std::array<Vertex, 36> verticies;
	memset(&verticies[0], 0, verticies.size() * sizeof(Vertex));
	
	Matrix44f m = Matrix44f::Identity;

	for (size_t i = 0; i < 4; i++)
	{
		verticies[i * 6 + 0].position = Vector4f(-skyboxSize, skyboxSize, -skyboxSize, 1.f) * m;
		verticies[i * 6 + 0].uv = quadSize * Vector2f(static_cast<float>(i), 1.f);

		verticies[i * 6 + 1].position = Vector4f(-skyboxSize, skyboxSize, skyboxSize, 1.f) * m;
		verticies[i * 6 + 1].uv = quadSize * Vector2f(static_cast<float>(i) + 1.f, 1.f);

		verticies[i * 6 + 2].position = Vector4f(-skyboxSize, -skyboxSize, -skyboxSize, 1.f) * m;
		verticies[i * 6 + 2].uv = quadSize * Vector2f(static_cast<float>(i), 2.f);

		verticies[i * 6 + 3].position = Vector4f(-skyboxSize, -skyboxSize, skyboxSize, 1.f) * m;
		verticies[i * 6 + 3].uv = quadSize * Vector2f(static_cast<float>(i) + 1.f, 2.f);

		verticies[i * 6 + 4].position = Vector4f(-skyboxSize, -skyboxSize, -skyboxSize, 1.f) * m;
		verticies[i * 6 + 4].uv = quadSize * Vector2f(static_cast<float>(i), 2.f);

		verticies[i * 6 + 5].position = Vector4f(-skyboxSize, skyboxSize, skyboxSize, 1.f) * m;
		verticies[i * 6 + 5].uv = quadSize * Vector2f(static_cast<float>(i) + 1.f, 1.f);

		m *= Matrix44f::CreateRotateAroundY(HalfPi);
	}

	// Bottom
	verticies[4 * 6 + 0].position = Vector4f(-skyboxSize, -skyboxSize, skyboxSize, 1.f) * m;
	verticies[4 * 6 + 0].uv = quadSize * Vector2f(1.f, 2.f);

	verticies[4 * 6 + 1].position = Vector4f(skyboxSize, -skyboxSize, skyboxSize, 1.f) * m;
	verticies[4 * 6 + 1].uv = quadSize * Vector2f(2.f, 2.f);

	verticies[4 * 6 + 2].position = Vector4f(-skyboxSize, -skyboxSize, -skyboxSize, 1.f) * m;
	verticies[4 * 6 + 2].uv = quadSize * Vector2f(1.f, 3.f);

	verticies[4 * 6 + 3].position = Vector4f(skyboxSize, -skyboxSize, -skyboxSize, 1.f) * m;
	verticies[4 * 6 + 3].uv = quadSize * Vector2f(2.f, 3.f);

	verticies[4 * 6 + 4].position = Vector4f(-skyboxSize, -skyboxSize, -skyboxSize, 1.f) * m;
	verticies[4 * 6 + 4].uv = quadSize * Vector2f(1.f, 3.f);

	verticies[4 * 6 + 5].position = Vector4f(skyboxSize, -skyboxSize, skyboxSize, 1.f) * m;
	verticies[4 * 6 + 5].uv = quadSize * Vector2f(2.f, 2.f);


	// Top
	verticies[5 * 6 + 0].position = Vector4f(-skyboxSize, skyboxSize, skyboxSize, 1.f) * m;
	verticies[5 * 6 + 0].uv = quadSize * Vector2f(1.f, 1.f);

	verticies[5 * 6 + 1].position = Vector4f(-skyboxSize, skyboxSize, -skyboxSize, 1.f) * m;
	verticies[5 * 6 + 1].uv = quadSize * Vector2f(1.f, 0.f);

	verticies[5 * 6 + 2].position = Vector4f(skyboxSize, skyboxSize, skyboxSize, 1.f) * m;
	verticies[5 * 6 + 2].uv = quadSize * Vector2f(2.f, 1.f);

	verticies[5 * 6 + 3].position = Vector4f(skyboxSize, skyboxSize, -skyboxSize, 1.f) * m;
	verticies[5 * 6 + 3].uv = quadSize * Vector2f(2.f, 0.f);

	verticies[5 * 6 + 4].position = Vector4f(skyboxSize, skyboxSize, skyboxSize, 1.f) * m;
	verticies[5 * 6 + 4].uv = quadSize * Vector2f(2.f, 1.f);

	verticies[5 * 6 + 5].position = Vector4f(-skyboxSize, skyboxSize, -skyboxSize, 1.f) * m;
	verticies[5 * 6 + 5].uv = quadSize * Vector2f(1.f, 0.f);
	 
	std::array<unsigned int, 36> indicies;
	for (size_t i = 0; i < indicies.size(); i++)
	{
		indicies[i] = static_cast<unsigned int>(i);
	}

	AddMesh(std::make_shared<Mesh<Vertex>>(aTexture, verticies, indicies));
}


Skybox::~Skybox()
{
}
