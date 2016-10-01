#include "stdafx.h"
#include "Engine\Rendering\SpriteRenderer.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "Engine\Sprite\Sprite.h"
#include "Engine\Sprite\QuadSpriteShape.h"
#include "Engine\Sprite\SpriteEffect.h"

namespace ENGINE_NAMESPACE
{

	SpriteRenderer::SpriteRenderer()
	{
		mySpriteEffect = std::make_shared<SpriteEffect>();
		myInstanceBuffer = std::make_unique<VertexBuffer<SpriteInstanceData>>(nullptr, 1, false);
		myQuad = std::make_unique<QuadSpriteShape>();
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Render(const Sprite &aSprite)
	{
		const std::shared_ptr<const Effect> & effect = aSprite.GetEffect();
		if (effect != nullptr)
		{
			effect->Bind();
		}
		else
		{
			mySpriteEffect->Bind();
		}


		SpriteInstanceData data;
		data.toWorld = aSprite.GenerateMatrix();
		data.color = aSprite.GetColor();
		myInstanceBuffer->UpdateData(&data, 1);
		myInstanceBuffer->Bind(1);

		aSprite.GetTexture()->BindToPS(0);
		Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Engine::GetRenderer().DisableDepthWrite();
		myQuad->RenderInstanced(1);
		Engine::GetRenderer().EnableDepthWrite();
	}
}
