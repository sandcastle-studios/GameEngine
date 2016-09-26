#include "stdafx.h"
#include "BlendState.h"
#include "Engine\Rendering\DXRenderer.h"
#include <d3d11.h>

BlendState::BlendState(const BlendStateDescription & aDescription)
{
	D3D11_BLEND_DESC d3d11Desc;

	d3d11Desc.AlphaToCoverageEnable = aDescription.alphaToCoverageEnable;
	d3d11Desc.IndependentBlendEnable = aDescription.independentBlendEnable;

	for (int i = 0; i < aDescription.renderTarget.size(); i++)
	{
		d3d11Desc.RenderTarget[i].BlendEnable = aDescription.renderTarget[i].blendEnable;

		d3d11Desc.RenderTarget[i].SrcBlend = static_cast<D3D11_BLEND>(aDescription.renderTarget[i].sourceBlend);
		d3d11Desc.RenderTarget[i].DestBlend = static_cast<D3D11_BLEND>(aDescription.renderTarget[i].destinationBlend);
		d3d11Desc.RenderTarget[i].BlendOp = static_cast<D3D11_BLEND_OP>(aDescription.renderTarget[i].blendOperation);

		d3d11Desc.RenderTarget[i].SrcBlendAlpha = static_cast<D3D11_BLEND>(aDescription.renderTarget[i].sourceBlendAlpha);
		d3d11Desc.RenderTarget[i].DestBlendAlpha = static_cast<D3D11_BLEND>(aDescription.renderTarget[i].destinationBlendAlpha);
		d3d11Desc.RenderTarget[i].BlendOpAlpha = static_cast<D3D11_BLEND_OP>(aDescription.renderTarget[i].blendOperationAlpha);

		d3d11Desc.RenderTarget[i].RenderTargetWriteMask = static_cast<UINT8>(aDescription.renderTarget[i].renderTargetWriteMask);
	}

	CheckDXError(
		Engine::GetRenderer().GetDevice()->CreateBlendState(&d3d11Desc, &myBlendState)
	);

	myDescription = aDescription;
}

BlendState::~BlendState()
{
	SAFE_RELEASE(myBlendState);
}

const BlendStateDescription & BlendState::GetDescription() const
{
	return myDescription;
}

void BlendState::Bind() const
{
	Engine::GetRenderer().GetContext()->OMSetBlendState(myBlendState, &myDescription.blendFactor[0], myDescription.sampleMask);
}

BlendStateDescription::BlendStateDescription()
{
	alphaToCoverageEnable = false;
	independentBlendEnable = false;

	for (int i = 0; i < renderTarget.size(); i++)
	{
		renderTarget[i].blendEnable = TRUE;
		renderTarget[i].sourceBlend = BlendFactor::eSourceAlpha;
		renderTarget[i].destinationBlend = BlendFactor::eInverseSourceAlpha;
		renderTarget[i].blendOperation = BlendOperation::eAdd;

		renderTarget[i].sourceBlendAlpha = BlendFactor::eOne;
		renderTarget[i].destinationBlendAlpha = BlendFactor::eInverseSourceAlpha;
		renderTarget[i].blendOperationAlpha = BlendOperation::eAdd;

		renderTarget[i].renderTargetWriteMask = ColorWriteMask::eWriteEnableAll;
	}

	for (int i = 0; i < blendFactor.size(); i++)
	{
		blendFactor[i] = 0.f;
	}

	sampleMask = 0xffffffff;
}
