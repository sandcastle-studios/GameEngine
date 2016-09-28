#pragma once

struct Vertex
{
	::Vector4f position;
	::Vector4f normal;
	::Vector4f tangent;
	::Vector4f bitangent;
	::Vector2f uv;
	
	::Vector3f GetPosition() const
	{
		return position;
	}
};
