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
	float4 diffuse : SV_TARGET0;
	float4 normal : SV_TARGET1;
	float4 worldPosition : SV_TARGET2;
};

cbuffer CameraCBuffer : register(b0)
{
	matrix toCamera;
	matrix toProjection;
	matrix projectionInverse;
	float4 cameraPosition;
};

Texture2D boundTexture : register( t0 );
Texture2D boundNormalMap : register( t1 );

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
	
	output.diffuse = boundTexture.Sample(samplerState, input.uv);
	
	float3 sampledNormal = (boundNormalMap.Sample(samplerState, input.uv).xyz * 2.f) - (1.f).xxx;
	
	float3x3 tangentSpaceMatrix = float3x3(
		normalize(input.bitangent.xyz),
		normalize(input.tangent.xyz),
		normalize(input.normal.xyz)
	);
	
	output.normal = float4(mul(sampledNormal, tangentSpaceMatrix).xyz, 1.f);
	
	output.worldPosition = input.worldPosition;
	
	return output;
}
