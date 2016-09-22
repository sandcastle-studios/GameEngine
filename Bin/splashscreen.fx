#include "noiseSimplex.fx"
#define Pi 3.14159265359

struct VertexInputType
{
	float4 position : POSITION;
	float4 normal : NORMAL;
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;
	float2 uv : TEXCOORD;

	matrix toWorld : INSTANCE_MATRIX;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
};

cbuffer SplashScreenCBuffer : register(b2)
{
	float4 time;
};

Texture2D boundTexture : register( t0 );
SamplerState samplerState;

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	output.position = input.position;
	output.uv = input.uv;
	
    return output;
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
	output.color = boundTexture.Sample(samplerState, input.uv);
	float t = saturate(-2.f + time[0] * 4.0f);
	float alpha;
	float progress = saturate((1.0f + sin(-Pi / 2.0f + (t / 4.0f) * Pi)) / 2.0f * 4.0f);
	float iProgress = 1.0f - progress;
	alpha = saturate((1.f + snoise(input.uv * 8.0f)) / 2.0f * saturate(10.0f - (length(input.uv.xy) * 14.0f * iProgress)) * progress * 10.f);
	output.color.xyz = (1.0f).xxx - ((1.0f).xxx - output.color.xyz) * alpha;
	return output;
}
