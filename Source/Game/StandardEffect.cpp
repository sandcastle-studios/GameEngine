#include "stdafx.h"
#include "StandardEffect.h"
#include <InputLayout.h>

StandardEffect::StandardEffect()
{
	AttachVertexShader("shader.fx", "VShader");
	AttachPixelShader("shader.fx", "PShader");

	InputLayout layout;
	layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT);
	layout.Add("TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT);

	Link(layout);
}

StandardEffect::~StandardEffect()
{
}
