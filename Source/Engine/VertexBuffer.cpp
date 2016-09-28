#include "stdafx.h"
#include "VertexBuffer.h"
#include "Engine.h"
#include <d3d11.h>
#include "DXRenderer.h"

GenericVertexBuffer::GenericVertexBuffer(const void *aData, int aSizeInBytes, int aVertexSize, bool aIsImmutable)
	: Buffer(D3D11_BIND_VERTEX_BUFFER, aIsImmutable ? D3D11_USAGE_IMMUTABLE : D3D11_USAGE_DYNAMIC, aIsImmutable ? 0 : D3D11_CPU_ACCESS_WRITE, 0, aData, aSizeInBytes)
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

int GenericVertexBuffer::GetVertexCount() const
{
	return GetSizeInBytes() / GetVertexSize();
}
