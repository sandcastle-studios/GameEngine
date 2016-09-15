#include "stdafx.h"
#include "SpriteRenderer.h"
#include "Effect.h"
#include "InputLayout.h"
#include "SpriteVertex.h"
#include "Model.h"
#include "DXRenderer.h"
#include "Mesh.h"

SpriteRenderer::SpriteRenderer()
{
	myEffect = std::make_shared<Effect>();
	myEffect->AttachVertexShader("sprite.fx", "VShader");
	myEffect->AttachPixelShader("sprite.fx", "PShader");

	InputLayout layout;
	layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);

	myEffect->Link(layout);

	std::array<SpriteVertex, 4> vertices =
	{
		SpriteVertex{ Vector4f(-1.f, 1.f, 0.5f, 1.f), Vector4f(0.f, 0.f, 0.f, 0.f) },
		SpriteVertex{ Vector4f(1.f, 1.f, 0.5f, 1.f), Vector4f(1.f, 0.f, 0.f, 0.f) },
		SpriteVertex{ Vector4f(-1.f, -1.f, 0.5f, 1.f), Vector4f(0.f, 1.f, 0.f, 0.f) },
		SpriteVertex{ Vector4f(1.f, -1.f, 0.5f, 1.f), Vector4f(1.f, 1.f, 0.f, 0.f) }
	};

	std::array<unsigned int, 6> indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	myUnitMesh = std::make_shared<Mesh<SpriteVertex>>(nullptr, vertices, indices);
	myUnitModel = std::make_unique<Model>(myEffect, myUnitMesh);
}


void SpriteRenderer::RenderWholeTexture(std::shared_ptr<Texture> aTexture, const Vector2f &aTopLeft, const Vector2f &aSize)
{
	Engine::GetInstance().GetRenderer().SetViewport(aTopLeft, aSize);
	myUnitMesh->SetTexture(aTexture);
	myUnitModel->Render(Matrix44f::Identity);
	myUnitMesh->SetTexture(nullptr);

	ID3D11ShaderResourceView * views[16] = { nullptr };
	Engine::GetInstance().GetRenderer().GetContext()->PSSetShaderResources(0, 16, views);
}

SpriteRenderer::~SpriteRenderer()
{
}
