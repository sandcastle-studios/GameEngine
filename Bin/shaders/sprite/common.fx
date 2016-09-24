
struct VertexInputType
{
    float4 position : POSITION;
	float2 uv : TEXCOORD0;
	
	matrix toWorld : INSTANCE_MATRIX;
	float4 color : INSTANCE_COLOR;
};
