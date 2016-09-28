#pragma once

struct LightConstantBufferData
{
	struct DirectionalLight
	{
		Vector4f myDirection;
		Vector4f myColor;
	} directionalLight[1];
	struct PointLight
	{
		Vector3f myPosition;
		float myIntensity;
		Vector3f myColor;
		float myRange;
	} myPointLight[8];

	unsigned int mipMapCount;
	Vector3f trash;
};
