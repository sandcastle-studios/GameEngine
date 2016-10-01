#include "stdafx.h"
#include "ConstantBuffer.h"
#include <d3d11.h>
#include "Engine\Rendering\DXRenderer.h"

namespace ENGINE_NAMESPACE
{
	GenericConstantBuffer::GenericConstantBuffer(const void * aData, int aSizeInBytes)
		: ShaderResourceBuffer(D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, 0, aData, aSizeInBytes)
	{

	}

	GenericConstantBuffer::~GenericConstantBuffer()
	{

	}

	void GenericConstantBuffer::BindToVS(int aSlot)
	{
		ID3D11Buffer * buffer = GetBuffer();
		Engine::GetInstance().GetRenderer().GetContext()->VSSetConstantBuffers(static_cast<UINT>(aSlot), 1, &buffer);
	}

	void GenericConstantBuffer::BindToPS(int aSlot)
	{
		ID3D11Buffer * buffer = GetBuffer();
		Engine::GetInstance().GetRenderer().GetContext()->PSSetConstantBuffers(static_cast<UINT>(aSlot), 1, &buffer);
	}

	void GenericConstantBuffer::BindToGS(int aSlot)
	{
		ID3D11Buffer * buffer = GetBuffer();
		Engine::GetInstance().GetRenderer().GetContext()->GSSetConstantBuffers(static_cast<UINT>(aSlot), 1, &buffer);
	}

	void GenericConstantBuffer::BindToCS(int aSlot)
	{
		ID3D11Buffer * buffer = GetBuffer();
		Engine::GetInstance().GetRenderer().GetContext()->CSSetConstantBuffers(static_cast<UINT>(aSlot), 1, &buffer);
	}

	void GenericConstantBuffer::BindToHS(int aSlot)
	{
		ID3D11Buffer * buffer = GetBuffer();
		Engine::GetInstance().GetRenderer().GetContext()->HSSetConstantBuffers(static_cast<UINT>(aSlot), 1, &buffer);
	}

	void GenericConstantBuffer::BindToDS(int aSlot)
	{
		ID3D11Buffer * buffer = GetBuffer();
		Engine::GetInstance().GetRenderer().GetContext()->DSSetConstantBuffers(static_cast<UINT>(aSlot), 1, &buffer);
	}
}
