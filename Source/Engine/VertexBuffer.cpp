#include "stdafx.h"
#include "VertexBuffer.h"
#include "Engine.h"
#include <d3d11.h>
#include "DXRenderer.h"

GenericVertexBuffer::GenericVertexBuffer(const void *aData, int aSizeInBytes, int aVertexSize)
	: Buffer(D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE, 0, 0, aData, aSizeInBytes)
{
	myVertexSize = aVertexSize;
}

GenericVertexBuffer::~GenericVertexBuffer()
{
}

void GenericVertexBuffer::Bind(int aSlot) const
{
	UINT vertexSize = static_cast<UINT>(GetVertexSize());
	UINT offset = 0;
	ID3D11Buffer * buffer = GetBuffer();
	Engine::GetInstance().GetRenderer().GetContext()->IASetVertexBuffers(aSlot, 1, &buffer, &vertexSize, &offset);
}

int GenericVertexBuffer::GetVertexSize() const
{
	return myVertexSize;
}
