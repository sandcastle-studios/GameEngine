#pragma once

struct VertexPosColUV
{
	::Vector4f position;
	::Vector4f color;
	::Vector2f uv;

	::Vector3f GetPosition() const
	{
		return position;
	}
};
