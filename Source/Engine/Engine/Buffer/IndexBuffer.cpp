#include "stdafx.h"
#include "Engine\Buffer\IndexBuffer.h"
#include <d3d11.h>
#include "Engine\Rendering\DXRenderer.h"

namespace ENGINE_NAMESPACE
{
	IndexBuffer::IndexBuffer(const unsigned int * aFirstIndex, unsigned int aIndexCount)
		: Buffer(D3D11_BIND_INDEX_BUFFER, D3D11_USAGE_IMMUTABLE, 0, 0, aFirstIndex, aIndexCount * sizeof(unsigned int))
	{
	}

	IndexBuffer::IndexBuffer(const std::vector<unsigned int> & aIndices)
		: IndexBuffer(&aIndices[0], static_cast<unsigned int>(aIndices.size()))
	{
	}

	void IndexBuffer::Bind()
	{
		Engine::GetInstance().GetRenderer().GetContext()->IASetIndexBuffer(GetBuffer(), DXGI_FORMAT_R32_UINT, 0);
	}

	int IndexBuffer::GetCount() const
	{
		return GetSizeInBytes() / sizeof(unsigned int);
	}

	IndexBuffer::~IndexBuffer()
	{
	}
}
