#include "common.fx"

PixelOutput PShader(PixelInput aInput)
{
	PixelOutput output;
	float3 toPixel = normalize(aInput.worldPosition.xyz - cameraPosition.xyz);
	float3 ambientLight = boundCubeMap.SampleLevel(samplerState, toPixel.xyz, 0).xyz;
	
	output.color.xyz = ambientLight;
	output.color.a = 1.0f;
	return output;
}
