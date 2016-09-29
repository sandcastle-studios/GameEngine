#define Pi 3.14159265359

struct VertexInput
{
    float4 position : POSITION;
    float4 normal : NORMAL;
    float4 tangent : TANGENT;
    float4 bitangent : BITANGENT;
	float2 uv : TEXCOORD;
	
	matrix toWorld : INSTANCE_MATRIX;
};

struct PixelInput
{
    float4 position : SV_POSITION;
	float4 worldPosition : POSITION;
	
	float4 normal : NORMAL;
    float4 tangent : TANGENT;
    float4 bitangent : BITANGENT;
	
    float2 uv : TEXCOORD;
};

struct PixelOutput
{
	float4 color : SV_TARGET;
};

cbuffer CameraCBuffer : register(b0)
{
	matrix toCamera;
	matrix toProjection;
	float4 cameraPosition;
};

cbuffer LightConstantBuffer : register(b1)
{
	struct DirectionLight
	{
		float4 direction;
		float4 color;
	} directionLight[1];
	
	float ambient;
	float3 _ambientPadding;

	uint cubeMipCount;
	uint3 _cubePadding;
};

Texture2D boundTexture : register( t0 );
Texture2D boundNormalMap : register( t1 );
Texture2D boundRoughnessMap : register(t2);
Texture2D boundAmbientOcclusionMap : register(t3);
Texture2D boundEmissiveMap : register(t4);
Texture2D boundMetalnessMap : register(t5);
TextureCube boundCubeMap : register(t6);

SamplerState samplerState;
