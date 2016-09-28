#include "stdafx.h"
#include "SkyboxEffect.h"
#include "InputLayout.h"


SkyboxEffect::SkyboxEffect()
{
	AttachVertexShader("shaders/shader.fx", "VShader");
	AttachPixelShader("shaders/shader.fx", "PixelShader_Skybox");

	InputLayout layout;
	layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("BITANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT);

	layout.AddPerInstance("INSTANCE_MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);

	Link(layout);
}


SkyboxEffect::~SkyboxEffect()
{
}
