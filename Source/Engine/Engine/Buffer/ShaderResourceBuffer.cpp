#include "stdafx.h"
#include "Engine\Buffer\ShaderResourceBuffer.h"

namespace ENGINE_NAMESPACE
{
	ShaderResourceBuffer::ShaderResourceBuffer(UINT aBindFlags, D3D11_USAGE aUsage, UINT aCpuAccessFlags, UINT aMiscFlags, const void * aData, int aSizeInBytes)
		: Buffer(aBindFlags, aUsage, aCpuAccessFlags, aMiscFlags, aData, aSizeInBytes)
	{
	}

	ShaderResourceBuffer::~ShaderResourceBuffer()
	{
	}

	void ShaderResourceBuffer::BindToVS(int aSlot)
	{
	}

	void ShaderResourceBuffer::BindToPS(int aSlot)
	{
	}

	void ShaderResourceBuffer::BindToGS(int aSlot)
	{
	}

	void ShaderResourceBuffer::BindToCS(int aSlot)
	{
	}

	void ShaderResourceBuffer::BindToHS(int aSlot)
	{
	}

	void ShaderResourceBuffer::BindToDS(int aSlot)
	{
	}
}
