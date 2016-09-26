#include "stdafx.h"
#include "MultiRenderTexture.h"
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Buffer\DepthBuffer.h"

MultiRenderTexture::MultiRenderTexture(int aBufferCount, int aWidth, int aHeight, bool aGenerateDepthBuffer)
{
	for (int i = 0; i < aBufferCount; i++)
	{
		myRenderTextures.push_back(std::make_shared<RenderTexture>(aWidth, aHeight, false));
	}

	if (aGenerateDepthBuffer)
	{
		myDepthBuffer = std::make_shared<DepthBuffer>(aWidth, aHeight);
	}

	myWidth = aWidth;
	myHeight = aHeight;
}

MultiRenderTexture::~MultiRenderTexture()
{
}

void MultiRenderTexture::Bind()
{
	Engine::GetRenderer().StoreRenderTargetResolution(Vector2f(static_cast<float>(myWidth), static_cast<float>(myHeight)));

	ID3D11RenderTargetView * views[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
	for (int i = 0; i < myRenderTextures.size(); i++)
	{
		views[i] = myRenderTextures[i]->GetView();
	}
	Engine::GetRenderer().GetContext()->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, views, myDepthBuffer->GetView());
}

const std::vector<std::shared_ptr<RenderTexture>> & MultiRenderTexture::GetRenderTextures() const
{
	return myRenderTextures;
}

const std::shared_ptr<DepthBuffer> & MultiRenderTexture::GetDepthBuffer() const
{
	return myDepthBuffer;
}

void MultiRenderTexture::Clear(const Vector4f & aColor)
{
	for (int i = 0; i < myRenderTextures.size(); i++)
	{
		myRenderTextures[i]->Clear(aColor);
	}
	myDepthBuffer->Clear();
}
