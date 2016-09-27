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
    float4 position : SV_POSITION; // Apparently in pixel space in the pixel shader?
	float4 projectionPosition : POSITION;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
};

cbuffer CameraCBuffer : register(b0)
{
	matrix toCamera;
	matrix toProjection;
	matrix projectionInverse;
	float4 cameraPosition;
};

cbuffer DeferredCBuffer : register(b2)
{
	float3 pointLightCenter;
	float pointLightRadius;
	float3 pointLightColor;
	float pointLightIntensity;
};

// Texture2D boundDepth : register(t2);
Texture2D boundDiffuse : register(t0);
Texture2D boundNormal : register(t1);
Texture2D boundPosition : register(t2);

SamplerState samplerState;

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	output.position = input.position;
	output.position = mul(input.toWorld, output.position);
	output.position = mul(toCamera, output.position);
	output.position = mul(toProjection, output.position);

	output.projectionPosition = output.position;
	output.projectionPosition /= output.position.w;
	
	// output.position.z = 0.5f;
	output.projectionPosition.z = 0.5f;

    return output;
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
	
	float2 uv = ((1.f).xx + input.projectionPosition.xy) / float2(2.f, 2.f);
	uv.y = 1.0f - uv.y;

	float3 sampledDiffuse = boundDiffuse.Sample(samplerState, uv).xyz;
	float3 normal = boundNormal.Sample(samplerState, uv).xyz;

	
	/*float sampledDepth = boundDepth.Sample(samplerState, uv).x;
	float3 projectionSpace = float3(input.projectionPosition.xy, sampledDepth);
	float4 worldPos = mul(projectionInverse, float4(projectionSpace, 1.0f));
	
	float3 worldPositionToShade = worldPos.xyz / worldPos.w;*/

	float3 worldPositionToShade = boundPosition.Sample(samplerState, uv).xyz;
	
	float3 toLight = pointLightCenter - worldPositionToShade;
	const float distance = length(toLight);
	float3 directionToLight = toLight / distance;

	float lambert = saturate(dot(normal, directionToLight));
	float attenuation = saturate(1.f - (distance / pointLightRadius));

	// output.lambert.w = distance < pointLightRadius ? 1.0f : 0.0f;
	output.color = float4(saturate(sampledDiffuse * pointLightColor * lambert.xxx * attenuation * pointLightIntensity), 1.0f);
	// output.lambert.xyz = float3(1.0f, 1.0f, 1.0f) * 0.1f;
	// output.lambert = float4(worldPositionToShade, 1.0f);

	return output;
}
