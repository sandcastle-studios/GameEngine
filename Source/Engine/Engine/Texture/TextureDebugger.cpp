#include "stdafx.h"
#include "Engine\Texture\TextureDebugger.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Effect\Effect.h"
#include "Engine\Effect\InputLayout.h"
#include "Engine\Model\Model.h"
#include "Engine\Buffer\DepthBuffer.h"
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Model\Mesh.h"
#include "Engine/Sprite/SpriteVertex.h"

TextureDebugger::TextureDebugger()
{
	/*
	myEffect = std::make_shared<Effect>();
	myEffect->AttachVertexShader("sprite.fx", "VShader");
	myEffect->AttachPixelShader("sprite.fx", "PShader");

	InputLayout layout;
	layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);

	myEffect->Link(layout);

	std::array<SpriteVertex, 4> vertices = 
	{
		SpriteVertex { Vector4f(-1.f, 1.f, 0.5f, 1.f), Vector2f(0.f, 0.f) },
		SpriteVertex { Vector4f(1.f, 1.f, 0.5f, 1.f), Vector2f(1.f, 0.f) },
		SpriteVertex { Vector4f(-1.f, -1.f, 0.5f, 1.f), Vector2f(0.f, 1.f) },
		SpriteVertex { Vector4f(1.f, -1.f, 0.5f, 1.f), Vector2f(1.f, 1.f) }
	};

	std::array<unsigned int, 6> indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	myUnitQuad = std::make_unique<Model>(std::make_unique<Mesh<SpriteVertex>>(nullptr, Surface(), vertices, indices));
	*/
}


TextureDebugger::~TextureDebugger()
{
}

void TextureDebugger::Render()
{
	/*myEffect->Bind();

	float height = Engine::GetInstance().GetRenderer().GetBackBuffer()->GetHeight() * 0.25f;
	float width = height;

	Engine::GetInstance().GetRenderer().GetBackBuffer()->GetDepthBuffer()->Unbind();
	
	for (size_t i = 0; i < myTexturesToDebug.size(); i++)
	{
		// myUnitQuad->SetTexture(myTexturesToDebug[i]);

		// Engine::GetInstance().GetRenderer().SetViewport(Vector2f(Engine::GetInstance().GetRenderer().GetWidth() - width, height * static_cast<float>(i)), Vector2f(width, height));
		
		// myUnitQuad->Render();
	}

	Engine::GetInstance().GetRenderer().ResetViewport();

	myTexturesToDebug.clear();*/
}

void TextureDebugger::QueueRender(std::shared_ptr<Texture> aTextureToView)
{
	myTexturesToDebug.push_back(aTextureToView);
}
