#include "stdafx.h"
#include "Engine\Effect\PixelShader.h"
#include "Engine\Rendering\DXRenderer.h"
#include <d3d11.h>

PixelShader::PixelShader(const std::string & aFileName, const char * aEntryPoint)
	: Shader(aFileName)
{
	myEntryPoint = aEntryPoint;
	myShader = nullptr;

	ID3D10Blob * blob = CreateShader(aFileName, aEntryPoint, "ps_5_0");

	CheckDXError(
		Engine::GetInstance().GetRenderer().GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &myShader);
	);

	blob->Release();
	blob = nullptr;
}

PixelShader::~PixelShader()
{
	SAFE_RELEASE(myShader);
}

void PixelShader::Bind() const
{
	Engine::GetInstance().GetRenderer().GetContext()->PSSetShader(myShader, nullptr, 0);
}

void PixelShader::Reload()
{
	SAFE_RELEASE(myShader);

	ID3D10Blob * blob = CreateShader(GetPath(), myEntryPoint.c_str(), "ps_5_0");

	CheckDXError(
		Engine::GetInstance().GetRenderer().GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &myShader);
	);
}
