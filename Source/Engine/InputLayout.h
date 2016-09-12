#pragma once
#include <d3d11.h>

class InputLayout
{
public:
	InputLayout();
	~InputLayout();

	void Add(const char *aSemanticName, const int aSemanticIndex, const DXGI_FORMAT aFormat);

	const D3D11_INPUT_ELEMENT_DESC *GetLayoutLocation() const;
	int GetLayoutCount() const;

private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> myDescription;
};

