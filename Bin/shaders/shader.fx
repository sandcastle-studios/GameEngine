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
	float4 worldPosition : POSITION;
	
	float4 normal : NORMAL;
    float4 tangent : TANGENT;
    float4 bitangent : BITANGENT;
	
    float2 uv : TEXCOORD;
};

struct PixelOutputType
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
	float3 ambientPadding;
};

Texture2D boundTexture : register( t0 );
Texture2D boundNormalMap : register( t1 );
Texture2D boundRougnessMap : register(t2);
Texture2D boundAmbientOcclusionMap : register(t3);
Texture2D boundEmissiveMap : register(t4);
Texture2D boundMetalnessMap : register(t5);

SamplerState samplerState;

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	output.position = input.position;
	output.position = mul(input.toWorld, output.position);
	output.worldPosition = output.position;
	output.position = mul(toCamera, output.position);
	output.position = mul(toProjection, output.position);
	
	output.normal = float4(mul((float3x3)input.toWorld, input.normal.xyz), 1.0f);
	output.tangent = float4(mul((float3x3)input.toWorld, input.tangent.xyz), 1.0f);
	output.bitangent = float4(mul((float3x3)input.toWorld, input.bitangent.xyz), 1.0f);
	
	output.uv = input.uv;
	
    return output;
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
	
	float3 sampledColor = boundTexture.Sample(samplerState, input.uv).xyz;
	float3 sampledNormal = (boundNormalMap.Sample(samplerState, input.uv).xyz * 2.f) - (1.f).xxx;
	float3 sampledRougness = boundRougnessMap.Sample(samplerState, input.uv).xyz;
	float3 sampledAmbientOcclusion = boundAmbientOcclusionMap.Sample(samplerState, input.uv).xyz;
	float3 sampledEmissive = boundEmissiveMap.Sample(samplerState, input.uv).xyz;
	float sampledMetalness = boundMetalnessMap.Sample(samplerState, input.uv).x;
	
	roughness = sampledRougness;

	float3x3 tangentSpaceMatrix = float3x3(
		normalize(input.bitangent.xyz),
		normalize(input.tangent.xyz),
		normalize(input.normal.xyz)
	);
	
	float3 normal = mul(sampledNormal, tangentSpaceMatrix);

	const float3 directionToLight = -directionLight[0].direction.xyz;
	
	float lambert = saturate(dot(normal, directionToLight));
	float3 directDiffuse = sampledColor * directionLight[0].color.xyz * lambert.xxx;
	
	output.color = float4(directDiffuse * (1.0f - ambient) + sampledColor * ambient, 1.0f);
	
	return output;
}
