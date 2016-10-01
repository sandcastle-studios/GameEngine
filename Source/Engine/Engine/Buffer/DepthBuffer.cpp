#include "stdafx.h"
#include "Engine\Buffer\DepthBuffer.h"
#include <d3d11.h>
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Texture\Texture.h"

namespace ENGINE_NAMESPACE
{
	DepthBuffer::DepthBuffer(unsigned int aWidth, unsigned int aHeight)
	{
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		memset(&depthBufferDesc, 0, sizeof(depthBufferDesc));

		depthBufferDesc.Width = aWidth;
		depthBufferDesc.Height = aHeight;
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;

		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateTexture2D(&depthBufferDesc, NULL, &myDepthStencilBuffer)
		);

		// Initialize the depth stencil view.
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		memset(&depthStencilViewDesc, 0, sizeof(depthStencilViewDesc));

		// Set up the depth stencil view description.
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // D3D11_DSV_DIMENSION_TEXTURE2DMS for multisample support;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		// CreateInputLayout the depth stencil view.
		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateDepthStencilView(myDepthStencilBuffer, &depthStencilViewDesc, &myDepthStencilView)
		);

		myResourceView = nullptr;

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceDesc;
		memset(&shaderResourceDesc, 0, sizeof(shaderResourceDesc));
		shaderResourceDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D; // D3D11_SRV_DIMENSION_TEXTURE2DMS for multisample support
		shaderResourceDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceDesc.Texture2D.MipLevels = static_cast<UINT>(-1);

		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateShaderResourceView(myDepthStencilBuffer, &shaderResourceDesc, &myResourceView);
		);

		myTexture = std::make_shared<Texture>(myDepthStencilBuffer, myResourceView, aWidth, aHeight);
	}

	DepthBuffer::~DepthBuffer()
	{
		SAFE_RELEASE(myDepthStencilView);
		SAFE_RELEASE(myDepthStencilBuffer);
		SAFE_RELEASE(myResourceView);
	}

	void DepthBuffer::Bind()
	{
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

		Engine::GetInstance().GetRenderer().GetContext()->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, renderTargets, myDepthStencilView);
	}

	void DepthBuffer::Unbind()
	{
		struct ID3D11RenderTargetView * renderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
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

		Engine::GetInstance().GetRenderer().GetContext()->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, renderTargets, nullptr);
	}

	void DepthBuffer::Clear()
	{
		Engine::GetInstance().GetRenderer().GetContext()->ClearDepthStencilView(myDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	void DepthBuffer::Clear(UINT aFlags, FLOAT aDepth, UINT8 aStencilMask)
	{
		Engine::GetInstance().GetRenderer().GetContext()->ClearDepthStencilView(myDepthStencilView, aFlags, aDepth, aStencilMask);
	}

	std::shared_ptr<Texture> DepthBuffer::GetTexture()
	{
		return myTexture;
	}

	ID3D11DepthStencilView * DepthBuffer::GetView()
	{
		return myDepthStencilView;
	}
}
