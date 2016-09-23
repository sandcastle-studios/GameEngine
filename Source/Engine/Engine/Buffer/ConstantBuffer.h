#pragma once
#include "Engine\Buffer\ShaderResourceBuffer.h"

class GenericConstantBuffer : public ShaderResourceBuffer
{
public:
	~GenericConstantBuffer();
	
	virtual void BindToVS(int aSlot) override;
	virtual void BindToPS(int aSlot) override;
	virtual void BindToGS(int aSlot) override;
	virtual void BindToCS(int aSlot) override;
	virtual void BindToHS(int aSlot) override;
	virtual void BindToDS(int aSlot) override;

protected:
	GenericConstantBuffer(const void * aData, int aSizeInBytes);
};

template <typename TData>
class ConstantBuffer : public GenericConstantBuffer
{
public:
	ConstantBuffer();
	ConstantBuffer(const TData & myData);
	void UpdateData(const TData & myData);
};

template <typename TData>
ConstantBuffer<TData>::ConstantBuffer()
	: GenericConstantBuffer(nullptr, sizeof(TData))
{
}

template <typename TData>
ConstantBuffer<TData>::ConstantBuffer(const TData & myData)
	: GenericConstantBuffer(&myData, sizeof(myData))
{
}

template <typename TData>
void ConstantBuffer<TData>::UpdateData(const TData & aData)
{
	GenericConstantBuffer::UpdateData(&aData, sizeof(aData), false);
}
