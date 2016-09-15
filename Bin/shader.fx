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
	
	const float3 lightDirection = normalize(float3(-1.0f, -1.0f, 1.0f));
	const float3 lightColor = float3(1.0f, 1.0f, 1.0f);
	
	float3 eyeDistance = cameraPosition.xyz - input.worldPosition.xyz;
	eyeDistance += -lightDirection;
	eyeDistance /= 2.0f;
	float3 halfAngleVector = normalize(eyeDistance);
	
	float normalLightDirDot = clamp(dot(input.normal.xyz, -lightDirection), 0.0f, 1.0f);
	float3 diffuse = (sampledColor * normalLightDirDot) * lightColor;
	
	float halfVectorNormal = clamp(dot(halfAngleVector, input.normal.xyz), 0.0f, 1.0f);
	float specularPower = 12.0f;
	halfVectorNormal = pow(halfVectorNormal, specularPower);
	
	float3 specular = lightColor * halfVectorNormal;
	
	output.color = float4(diffuse + specular, 1.0f);
	output.color.r = clamp(output.color.r, 0.0f, 1.0f);
	output.color.g = clamp(output.color.g, 0.0f, 1.0f);
	output.color.b = clamp(output.color.b, 0.0f, 1.0f);
	
	const float globalIllumination = 0.2f;
	output.color = output.color * (1.0f - globalIllumination) + float4(sampledColor, 1.0f) * globalIllumination;
	
	return output;
}
