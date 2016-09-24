#include "stdafx.h"
#include <d3d11.h>
#include "Engine\Effect\Effect.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Effect\VertexShader.h"
#include "Engine\Effect\PixelShader.h"
#include "Engine\Engine.h"
#include "Engine\Effect\InputLayout.h"

Effect::Effect()
{
	myVertexShader = nullptr;
	myPixelShader = nullptr;
	myLayout = nullptr;

	myIsLinked = false;
}

Effect::~Effect()
{
	delete myVertexShader;
	myVertexShader = nullptr;
	delete myPixelShader;
	myPixelShader = nullptr;

	if (myLayout != nullptr)
	{
		myLayout->Release();
		myLayout = nullptr;
	}
}

void Effect::AttachVertexShader(const std::string & aFileName, const char * aEntryPoint)
{
	assert("Effect already linked" && myIsLinked == false);
	assert("Vertex shader already attached" && myVertexShader == nullptr);
	myVertexShader = new VertexShader(aFileName, aEntryPoint);
}

void Effect::AttachPixelShader(const std::string & aFileName, const char * aEntryPoint)
{
	assert("Effect already linked" && myIsLinked == false);
	assert("Pixel shader already attached" && myPixelShader == nullptr);
	myPixelShader = new PixelShader(aFileName, aEntryPoint);
}

void Effect::Link(const InputLayout & aLayoutDescription)
{
	assert("Effect already linked" && myIsLinked == false);

	if (myVertexShader != nullptr)
	{
		myLayout = myVertexShader->CreateLayout(aLayoutDescription);
	}

	myIsLinked = true;
}

void Effect::Bind() const
{
	if (myVertexShader != nullptr)
	{
		myVertexShader->Bind();
	}
	else
	{
		Engine::GetInstance().GetRenderer().GetContext()->VSSetShader(nullptr, nullptr, 0);
	}

	if (myPixelShader != nullptr)
	{
		myPixelShader->Bind();
	}
	else
	{
		Engine::GetInstance().GetRenderer().GetContext()->PSSetShader(nullptr, nullptr, 0);
	}
	
	if (myLayout != nullptr)
	{
		Engine::GetInstance().GetRenderer().GetContext()->IASetInputLayout(myLayout);
	}
	else
	{
		Engine::GetInstance().GetRenderer().GetContext()->IASetInputLayout(nullptr);
	}
}
