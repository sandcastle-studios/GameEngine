#include "stdafx.h"
#include "SpriteShape.h"
#include "Engine/Sprite/SpriteVertex.h"
#include "Engine/Buffer/VertexBuffer.h"
#include "Engine/Buffer/IndexBuffer.h"

namespace ENGINE_NAMESPACE
{
	SpriteShape::SpriteShape()
	{
	}

	void SpriteShape::CreateBuffers(const SpriteVertex * aVertices, const int aVertexCount, const unsigned int * aIndices, const int aIndexCount)
	{
		myVertexBuffer = std::make_unique<VertexBuffer<SpriteVertex>>(aVertices, aVertexCount);
		myIndexBuffer = std::make_unique<IndexBuffer>(aIndices, aIndexCount);
	}

	SpriteShape::~SpriteShape()
	{
	}

	void SpriteShape::RenderInstanced(const int aInstanceCount)
	{
		myVertexBuffer->Bind(0);
		myIndexBuffer->Bind();

		Engine::GetRenderer().GetContext()->DrawIndexedInstanced(static_cast<UINT>(myIndexBuffer->GetCount()), static_cast<UINT>(aInstanceCount), 0, 0,
			0);
	}
}
