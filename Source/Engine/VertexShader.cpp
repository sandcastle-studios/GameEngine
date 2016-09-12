#include "stdafx.h"
#include "VertexShader.h"
#include "DXRenderer.h"
#include <d3d11.h>
#include "InputLayout.h"

VertexShader::VertexShader(const char * aFileName, const char * aEntryPoint)
{
	ID3D10Blob * blob = CreateShader(aFileName, aEntryPoint, "vs_5_0");
	
	CheckDXError(
		Engine::GetInstance().GetRenderer().GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &myShader);
	);

	myBlob = blob;
}

VertexShader::~VertexShader()
{
	if (myShader)
	{
		myShader->Release();
		myShader = nullptr;
	}

	if (myBlob)
	{
		myBlob->Release();
		myBlob = nullptr;
	}
}

void VertexShader::Bind() const
{
	Engine::GetInstance().GetRenderer().GetContext()->VSSetShader(myShader, nullptr, 0);
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
