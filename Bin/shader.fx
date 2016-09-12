struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
	float2 uv : TEXCOORD0;
	float2 padding : TEXCOORD1;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
};


cbuffer CameraCBuffer : register(b0)
{
	matrix toCamera;
	matrix toProjection;
}

cbuffer InstanceCBuffer : register(b1)
{
	matrix toWorld;
}

Texture2D boundTexture : register( t0 );
SamplerState samplerState;

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	output.position = input.position;
	output.position = mul(toWorld, output.position);
	output.position = mul(toCamera, output.position);
	output.position = mul(toProjection, output.position);
	
	output.color = input.color;
	output.uv = input.uv;
	
    return output;
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
	output.color = boundTexture.Sample(samplerState, input.uv);
	output.color *= input.color;
	
	return output;
}
