#pragma once
#include "Engine\Buffer\Buffer.h"

namespace ENGINE_NAMESPACE
{
	class ShaderResourceBuffer : public Buffer
	{
	public:
		~ShaderResourceBuffer();

		virtual void BindToVS(int aSlot) = 0;
		virtual void BindToPS(int aSlot) = 0;
		virtual void BindToGS(int aSlot) = 0;
		virtual void BindToCS(int aSlot) = 0;
		virtual void BindToHS(int aSlot) = 0;
		virtual void BindToDS(int aSlot) = 0;

	protected:
		ShaderResourceBuffer(UINT aBindFlags, D3D11_USAGE aUsage, UINT aCpuAccessFlags, UINT aMiscFlags, const void * aData, int aSizeInBytes);
	};
}
