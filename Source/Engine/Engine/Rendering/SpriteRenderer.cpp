#include "stdafx.h"
#include "Engine\Rendering\SpriteRenderer.h"
#include "Engine\Effect\Effect.h"
#include "Engine\Effect\InputLayout.h"
#include "Engine\SpriteVertex.h"
#include "Engine\Model\Model.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Model\Mesh.h"
#include "Engine\Rendering\ModelRenderer.h"
#include "Engine\Vertex.h"

SpriteRenderer::SpriteRenderer()
{
	std::array<Vertex, 4> vertices =
	{
		Vertex{ Vector4f(-1.f, 1.f, 0.5f, 1.f)	, Vector4f(0.f, 0.f, -1.f, 0.f), Vector4f::Zero, Vector4f::Zero, Vector2f(0.f, 0.f) },
		Vertex{ Vector4f(1.f, 1.f, 0.5f, 1.f)	, Vector4f(0.f, 0.f, -1.f, 0.f), Vector4f::Zero, Vector4f::Zero, Vector2f(1.f, 0.f) },
		Vertex{ Vector4f(-1.f, -1.f, 0.5f, 1.f)	, Vector4f(0.f, 0.f, -1.f, 0.f), Vector4f::Zero, Vector4f::Zero, Vector2f(0.f, 1.f) },
		Vertex{ Vector4f(1.f, -1.f, 0.5f, 1.f)	, Vector4f(0.f, 0.f, -1.f, 0.f), Vector4f::Zero, Vector4f::Zero, Vector2f(1.f, 1.f) }
	};
	
	std::array<unsigned int, 6> indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	myUnitMesh = std::make_shared<Mesh<Vertex>>(nullptr, vertices, indices);
	myUnitModel = std::make_unique<Model>(nullptr, myUnitMesh);
}


void SpriteRenderer::RenderWholeTexture(std::shared_ptr<Texture> aTexture, const Vector2f &aTopLeft, const Vector2f &aSize, const std::shared_ptr<Effect> * aEffect)
{
	Engine::GetInstance().GetRenderer().SetViewport(aTopLeft, aSize);
	myUnitMesh->SetTexture(0, aTexture);

	if (aEffect != nullptr)
	{
		myUnitMesh->SetEffect(*aEffect);
	}

	myUnitModel->InstantRender(Matrix44f::Identity);
	
	myUnitMesh->SetTexture(0, nullptr);
}

SpriteRenderer::~SpriteRenderer()
{
}
