#include "stdafx.h"
#include "RenderTexture.h"
#include "Texture.h"
#include "DXRenderer.h"
#include <d3d11.h>

RenderTexture::RenderTexture(unsigned int aWidth, unsigned int aHeight)
{
	myTexture = std::make_shared<Texture>(aWidth, aHeight, true);

	CheckDXError(
		Engine::GetInstance().GetRenderer().GetDevice()->CreateRenderTargetView(myTexture->GetTexture(), nullptr, &myRenderTargetView);
	);
}

RenderTexture::RenderTexture(ID3D11RenderTargetView * aRenderTarget)
{
	myRenderTargetView = aRenderTarget;
}

RenderTexture::~RenderTexture()
{
}

void RenderTexture::Bind(int aSlot)
{
	ID3D11RenderTargetView * renderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	ID3D11DepthStencilView * depthStencilView;
	Engine::GetInstance().GetRenderer().GetContext()->OMGetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, renderTargets, &depthStencilView);

	renderTargets[aSlot] = myRenderTargetView;

	Engine::GetInstance().GetRenderer().GetContext()->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, renderTargets, depthStencilView);
}

std::shared_ptr<Texture> RenderTexture::GetTexture()
{
	return myTexture;
}
