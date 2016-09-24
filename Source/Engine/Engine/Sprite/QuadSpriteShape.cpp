#include "stdafx.h"
#include "QuadSpriteShape.h"
#include "Engine\Sprite\SpriteVertex.h"

QuadSpriteShape::QuadSpriteShape()
{
	std::array<SpriteVertex, 4> vertices =
	{
		SpriteVertex{ Vector4f(0.f, 1.f, 0.5f, 1.f),  Vector2f(0.f, 1.f) },
		SpriteVertex{ Vector4f(1.f, 1.f, 0.5f, 1.f),   Vector2f(1.f, 1.f) },
		SpriteVertex{ Vector4f(0.f, 0.f, 0.5f, 1.f), Vector2f(0.f, 0.f) },
		SpriteVertex{ Vector4f(1.f, 0.f, 0.5f, 1.f),  Vector2f(1.f, 0.f) }
	};

	std::array<unsigned int, 6> indices =
	{
		1, 0, 2,
		1, 2, 3
	};

	CreateBuffers(&vertices[0], static_cast<int>(vertices.size()), &indices[0], static_cast<int>(indices.size()));
}

QuadSpriteShape::~QuadSpriteShape()
{
}
