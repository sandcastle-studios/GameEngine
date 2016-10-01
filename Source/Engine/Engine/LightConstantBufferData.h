#pragma once

namespace ENGINE_NAMESPACE
{
	struct LightConstantBufferData
	{
		struct DirectionLight
		{
			Vector4f direction;
			Vector4f color;
		} directionLight[1];

		float ambient;
		float _ambientPadding[3];

		unsigned int myCubeMapMipMaps;
		unsigned int _mcmmmPadding[3];
	};
}
