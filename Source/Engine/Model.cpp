#include "stdafx.h"
#include "Model.h"
#include <d3dcommon.h>
#include <d3d11.h>
#include "SimpleVertex.h"
#include "VertexBuffer.h"
#include "DXRenderer.h"
#include "IndexBuffer.h"
#include "Effect.h"
#include "Texture.h"

GenericModel::GenericModel(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture)
{
	myVertexCount = 0;
	myIndexCount = 0;

	myEffect = aEffect;
	myTexture = aTexture;
}

GenericModel::~GenericModel()
{
}

void GenericModel::SetTexture(std::shared_ptr<Texture> aTexture)
{
	myTexture = aTexture;
}

void GenericModel::Render() const
{
	if (myEffect != nullptr)
	{
		myEffect->Bind();
	}
	if (myTexture != nullptr)
	{
		myTexture->BindToPS(0);
	}

	myVertexBuffer->Bind(0);
	Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	myIndexBuffer->Bind();
	Engine::GetInstance().GetRenderer().GetContext()->DrawIndexed(myIndexCount, 0, 0);
}

void GenericModel::RenderInstanced(int aInstanceCount) const
{
	if (myEffect != nullptr)
	{
		myEffect->Bind();
	}
	if (myTexture != nullptr)
	{
		myTexture->BindToPS(0);
	}

	myVertexBuffer->Bind(0);
	Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	myIndexBuffer->Bind();
	Engine::GetInstance().GetRenderer().GetContext()->DrawIndexedInstanced(myIndexCount, aInstanceCount, 0, 0, 0);
}

std::shared_ptr<Texture> GenericModel::GetTexture()
{
	return myTexture;
}

void GenericModel::CreateModel(const void * aVertexData, int aVertexCount, int aVertexSizeInBytes, const unsigned int * aIndexData, int aIndexCount)
{
	if (myVertexBuffer != nullptr)
	{
		Error("Model already created!");
		return;
	}

	myVertexBuffer = std::make_unique<GenericVertexBuffer>(aVertexData, aVertexCount * aVertexSizeInBytes, aVertexSizeInBytes);
	myIndexBuffer = std::make_unique<IndexBuffer>(aIndexData, aIndexCount);

	myVertexCount = aVertexCount;
	myIndexCount = aIndexCount;
}
