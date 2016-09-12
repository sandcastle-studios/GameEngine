#include "stdafx.h"
#include "InputLayout.h"

InputLayout::InputLayout()
{
}

InputLayout::~InputLayout()
{
}

void InputLayout::Add(const char *aSemanticName, const int aSemanticIndex, const DXGI_FORMAT aFormat)
{
	D3D11_INPUT_ELEMENT_DESC desc;

	desc.SemanticName = aSemanticName;
	desc.SemanticIndex = aSemanticIndex;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.InputSlot = 0;
	desc.AlignedByteOffset = myDescription.size() > 0 ? D3D11_APPEND_ALIGNED_ELEMENT : 0;
	desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	desc.InstanceDataStepRate = 0;

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
