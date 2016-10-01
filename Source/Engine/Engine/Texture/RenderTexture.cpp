#include "stdafx.h"
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Rendering\DXRenderer.h"
#include <d3d11.h>
#include "Engine\Buffer\DepthBuffer.h"

namespace ENGINE_NAMESPACE
{
	RenderTexture::RenderTexture(unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer)
	{
		myTexture = std::make_shared<Texture>(aWidth, aHeight, true);

		if (aGenerateDepthBuffer)
		{
			myDepthBuffer = std::make_unique<DepthBuffer>(aWidth, aHeight);
		}

		myWidth = aWidth;
		myHeight = aHeight;

		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateRenderTargetView(myTexture->GetTexture(), nullptr, &myRenderTargetView);
		);
	}

	RenderTexture::RenderTexture(ID3D11Texture2D * aTexture, ID3D11RenderTargetView * aRenderTarget, ID3D11ShaderResourceView * aShaderResourceView, unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer)
	{
		myTexture = std::make_shared<Texture>(aTexture, aShaderResourceView, aWidth, aHeight);

		myRenderTargetView = aRenderTarget;
		myRenderTargetView->AddRef();

		if (aGenerateDepthBuffer)
		{
			myDepthBuffer = std::make_unique<DepthBuffer>(aWidth, aHeight);
		}

		myWidth = aWidth;
		myHeight = aHeight;
	}

	RenderTexture::~RenderTexture()
	{
		SAFE_RELEASE(myRenderTargetView);
	}

	void RenderTexture::Bind(int aSlot, bool aUpdateViewport)
	{
		Engine::GetRenderer().StoreRenderTargetResolution(Vector2f(static_cast<float>(myWidth), static_cast<float>(myHeight)));

		ID3D11RenderTargetView * renderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
		ID3D11DepthStencilView * depthStencilView;
		Engine::GetInstance().GetRenderer().GetContext()->OMGetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, renderTargets, &depthStencilView);

		for (size_t i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
		{
			if (renderTargets[i])
			{
				renderTargets[i]->Release();
			}
		}

		if (depthStencilView)
		{
			depthStencilView->Release();
		}

		renderTargets[aSlot] = myRenderTargetView;

		if (myDepthBuffer != nullptr)
		{
			depthStencilView = myDepthBuffer->GetView();
		}

		Engine::GetInstance().GetRenderer().GetContext()->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, renderTargets, depthStencilView);

		if (aUpdateViewport)
		{
			Engine::GetInstance().GetRenderer().SetViewport(Vector2f::Zero, Vector2f(static_cast<float>(myWidth), static_cast<float>(myHeight)));
		}
	}

	unsigned int RenderTexture::GetWidth() const
	{
		return myWidth;
	}

	unsigned int RenderTexture::GetHeight() const
	{
		return myHeight;
	}

	const std::shared_ptr<Texture> & RenderTexture::GetTexture()
	{
		return myTexture;
	}

	const std::shared_ptr<DepthBuffer> & RenderTexture::GetDepthBuffer()
	{
		return myDepthBuffer;
	}

	std::shared_ptr<const DepthBuffer> RenderTexture::GetDepthBuffer() const
	{
		return myDepthBuffer;
	}

	void RenderTexture::Clear(const Vector4f & aColor)
	{
		Engine::GetInstance().GetRenderer().GetContext()->ClearRenderTargetView(myRenderTargetView, reinterpret_cast<const float*>(&aColor));

		if (myDepthBuffer)
		{
			myDepthBuffer->Clear();
		}
	}
}
