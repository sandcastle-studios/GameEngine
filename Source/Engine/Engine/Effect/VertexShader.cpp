#include "stdafx.h"
#include "Engine\Effect\VertexShader.h"
#include "Engine\Rendering\DXRenderer.h"
#include <d3d11.h>
#include "Engine\Effect\InputLayout.h"

VertexShader::VertexShader(const std::string & aFileName, const char * aEntryPoint)
	: Shader(aFileName)
{
	myEntryPoint = aEntryPoint;
	myShader = nullptr;
	myBlob = nullptr;

	Reload();
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(myShader);
	SAFE_RELEASE(myBlob);
}

void VertexShader::Bind() const
{
	Engine::GetInstance().GetRenderer().GetContext()->VSSetShader(myShader, nullptr, 0);
}

void VertexShader::Reload()
{
	SAFE_RELEASE(myShader);
	SAFE_RELEASE(myBlob);

	ID3D10Blob * blob = CreateShader(GetPath(), myEntryPoint.c_str(), "vs_5_0");

	CheckDXError(
		Engine::GetInstance().GetRenderer().GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &myShader);
	);

	myBlob = blob;
}

ID3D11InputLayout * VertexShader::CreateLayout(const InputLayout & aLayoutDescription)
{
	ID3D11InputLayout * layout;

	CheckDXError(
		Engine::GetInstance().GetRenderer().GetDevice()->CreateInputLayout(
			aLayoutDescription.GetLayoutLocation(), aLayoutDescription.GetLayoutCount(),
			myBlob->GetBufferPointer(), myBlob->GetBufferSize(),
			&layout
		)
	);

	return layout;
}
