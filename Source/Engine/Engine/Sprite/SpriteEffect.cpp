#include "stdafx.h"
#include "SpriteEffect.h"

SpriteEffect::SpriteEffect()
{
	AttachVertexShader("shaders/sprite.fx", "VShader");
	AttachPixelShader("shaders/sprite.fx", "PShader");

	InputLayout layout;
	layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT);

	layout.AddPerInstance("INSTANCE_MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);

	layout.AddPerInstance("INSTANCE_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);

	Link(layout);
}

SpriteEffect::~SpriteEffect()
{
}
