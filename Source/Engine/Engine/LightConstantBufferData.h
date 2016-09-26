#pragma once

struct PointLight
{
	Vector3f position;
	float radius;
	Vector3f color;
	float intensity;
};

struct LightConstantBufferData
{
	struct DirectionLight
	{
		Vector4f direction;
		Vector4f color;
	} directionLight[1];

	PointLight pointLight[8];
};
