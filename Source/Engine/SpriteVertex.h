#pragma once

struct SpriteVertex
{
	Vector4f position;
	Vector4f uv;

	Vector3f GetPosition() const
	{
		return position;
	}
};
