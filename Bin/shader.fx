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
}

cbuffer BlendCBuffer : register(b1)
{
	float4 blendColor;
}

Texture2D boundTexture : register( t0 );
SamplerState samplerState;

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	output.position = input.position;
	output.position = mul(input.toWorld, output.position);
	output.worldPosition = output.position;
	output.position = mul(toCamera, output.position);
	output.position = mul(toProjection, output.position);
	
	output.normal = float4(mul((float3x3)input.toWorld, input.normal.xyz), 0.0f);
	output.uv = input.uv;
	
    return output;
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
	
	float3 sampledColor = boundTexture.Sample(samplerState, input.uv).xyz;
	
	const float3 directionToLight = normalize(float3(1.0f, 1.0f, -1.0f));
	const float3 lightColor = float3(1.0f, 1.0f, 1.0f) * 0.5f;
	
	float3 toEye = cameraPosition.xyz - input.worldPosition.xyz;
	float3 toEyeNormal = normalize(toEye);
	
	float3 normal = normalize(input.normal.xyz);
	
	output.color = float4(sampledColor.xyz, 1.0f) * blendColor;
	
	return output;
}
