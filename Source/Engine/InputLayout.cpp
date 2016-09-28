#include "stdafx.h"
#include "InputLayout.h"

InputLayout::InputLayout()
{
	myPerVertexCount = 0;
	myPerInstanceCount = 0;
}

InputLayout::~InputLayout()
{
}

void InputLayout::Add(const char *aSemanticName, const int aSemanticIndex, const DXGI_FORMAT aFormat, int aInputSlot)
{
	if (myPerInstanceCount > 0)
	{
		Error("Per Instance layout descriptions must be added last!");
	}

	D3D11_INPUT_ELEMENT_DESC desc;

	desc.SemanticName = aSemanticName;
	desc.SemanticIndex = aSemanticIndex;
	desc.Format = aFormat;
	desc.InputSlot = aInputSlot;
	desc.AlignedByteOffset = myDescription.size() > 0 ? D3D11_APPEND_ALIGNED_ELEMENT : 0;
	desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	desc.InstanceDataStepRate = 0;

	myPerVertexCount++;
	myDescription.push_back(desc);
}

void InputLayout::AddPerInstance(const char *aSemanticName, const int aSemanticIndex, const DXGI_FORMAT aFormat, int aInputSlot)
{
	D3D11_INPUT_ELEMENT_DESC desc;

	desc.SemanticName = aSemanticName;
	desc.SemanticIndex = aSemanticIndex;
	desc.Format = aFormat;
	desc.InputSlot = aInputSlot;
	desc.AlignedByteOffset = myPerInstanceCount > 0 ? D3D11_APPEND_ALIGNED_ELEMENT : 0;
	desc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	desc.InstanceDataStepRate = 1;

	myPerInstanceCount++;
	myDescription.push_back(desc);
}

const D3D11_INPUT_ELEMENT_DESC * InputLayout::GetLayoutLocation() const
{
	return &myDescription[0];
}

int InputLayout::GetLayoutCount() const
{
	return static_cast<int>(myDescription.size());
}
