struct VertexInputType
{
    float4 position : POSITION;
	float4 uv : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 uv : TEXCOORD0;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
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
	return output;
}
