#pragma once

namespace ENGINE_NAMESPACE
{
	struct LineVertex
	{
		Vector4f position;
		Vector4f color;

		Vector3f GetPosition() const
		{
			return position;
		}
	};
}
