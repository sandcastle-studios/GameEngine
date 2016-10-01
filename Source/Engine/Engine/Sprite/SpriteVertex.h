#pragma once

namespace ENGINE_NAMESPACE
{
	struct SpriteVertex
	{
		Vector4f position;
		Vector2f uv;

		Vector3f GetPosition() const
		{
			return position;
		}
	};
}
