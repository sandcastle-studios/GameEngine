#include "stdafx.h"
#include "Engine\Effect\StandardEffect.h"
#include "Engine\Effect\InputLayout.h"

StandardEffect::StandardEffect()
{
	AttachVertexShader("shaders/pbr/vertex.fx", "VShader");
	AttachPixelShader("shaders/pbr/pixel.fx", "PShader");

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

StandardEffect::~StandardEffect()
{
}
