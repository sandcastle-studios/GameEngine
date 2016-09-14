#pragma once

struct VertexPosColUV
{
	::Vector4f position;
	::Vector4f normal;
	::Vector4f tangent;
	::Vector4f bitangent;
	::Vector2f uv;
	::Vector4f bones1;
	::Vector4f bones2;
	
	::Vector3f GetPosition() const
	{
		return position;
	}
};
