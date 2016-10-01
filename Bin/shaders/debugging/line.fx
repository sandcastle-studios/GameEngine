cbuffer CameraCBuffer : register(b0)
{
    matrix toCamera;
    matrix toProjection;
    float4 cameraPosition;
};

struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float4 color : COLOR0;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
};

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
    output.position = mul(toCamera, input.position);
    output.position = mul(toProjection, output.position);
	output.color = input.color;
	
    return output;
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
	output.color = input.color;
	return output;
}
