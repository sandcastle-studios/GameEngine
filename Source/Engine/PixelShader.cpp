#include "stdafx.h"
#include "PixelShader.h"
#include "DXRenderer.h"
#include <d3d11.h>

PixelShader::PixelShader(const char * aFileName, const char * aEntryPoint)
{
	ID3D10Blob * blob = CreateShader(aFileName, aEntryPoint, "ps_5_0");

	CheckDXError(
		Engine::GetInstance().GetRenderer().GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &myShader);
	);

	blob->Release();
	blob = nullptr;
}

PixelShader::~PixelShader()
{
	if (myShader)
	{
		myShader->Release();
		myShader = nullptr;
	}
}

void PixelShader::Bind() const
{
	Engine::GetInstance().GetRenderer().GetContext()->PSSetShader(myShader, nullptr, 0);
}
