#include "stdafx.h"
#include "Engine\Texture\TextureDebugger.h"
#include "Engine\Rendering\DXRenderer.h"

TextureDebugger::TextureDebugger()
{
}


TextureDebugger::~TextureDebugger()
{
}

void TextureDebugger::Render()
{
	float height = Engine::GetRenderer().GetRenderTargetResolution().y * 0.2f;
	float width = height;
	
	for (size_t i = 0; i < myTexturesToDebug.size(); i++)
	{
		mySprite.SetTexture(myTexturesToDebug[i]);
		mySprite.SetPosition(Vector2f(Engine::GetRenderer().GetRenderTargetResolution().x - width, height * i + i * 1.f));
		mySprite.SetScale(Vector2f(width, height) / mySprite.GetTexture()->GetSize());
		mySprite.Render();
	}
	
	myTexturesToDebug.clear();
}

void TextureDebugger::QueueRender(std::shared_ptr<Texture> aTextureToView)
{
	myTexturesToDebug.push_back(aTextureToView);
}
