#include "sprite/common.fx"

struct PixelInputType
{
    float4 position : SV_POSITION;
	float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
};


Texture2D diffuse : register( t0 );
Texture2D lambert : register( t1 );
SamplerState samplerState;

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	output.position = mul(input.toWorld, input.position);
	output.color = input.color;
	output.uv = input.uv;
	
    return output;
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
	float3 diffuseColor = diffuse.Sample(samplerState, input.uv).xyz;
	float3 lambertColor = lambert.Sample(samplerState, input.uv).xyz;
	output.color = float4(diffuseColor * lambertColor, 1.0f) * input.color;
	return output;
}
