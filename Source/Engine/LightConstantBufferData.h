#pragma once

struct LightConstantBufferData
{
	struct DirectionLight
	{
		Vector4f direction;
		Vector4f color;
	} directionLight[1];
};
