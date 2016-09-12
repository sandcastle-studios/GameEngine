#pragma once
#include "Buffer.h"

class GenericVertexBuffer : public Buffer
{
public:
	GenericVertexBuffer(const void * aData, int aSizeInBytes, int aVertexSize);
	~GenericVertexBuffer();

	int GetVertexSize() const;
	void Bind(int aSlot) const;

private:
	int myVertexSize;
};

template<typename TVertex>
class VertexBuffer : public GenericVertexBuffer
{
public:
	VertexBuffer(const TVertex *aInitialData, int aVertexCount);
	~VertexBuffer();
};

template<typename TVertex>
VertexBuffer<TVertex>::VertexBuffer(const TVertex *aInitialData, int aVertexCount)
	: GenericVertexBuffer(aInitialData, sizeof(TVertex) * aVertexCount, sizeof(TVertex))
{
}

template<typename TVertex>
VertexBuffer<TVertex>::~VertexBuffer()
{
}
