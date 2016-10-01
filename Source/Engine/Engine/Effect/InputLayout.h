#pragma once
#include <d3d11.h>

namespace ENGINE_NAMESPACE
{
	class InputLayout
	{
	public:
		InputLayout();
		~InputLayout();

		void Add(const char *aSemanticName, const int aSemanticIndex, const DXGI_FORMAT aFormat, int aInputSlot = 0);
		void AddPerInstance(const char *aSemanticName, const int aSemanticIndex, const DXGI_FORMAT aFormat, int aInputSlot = 0);

		const D3D11_INPUT_ELEMENT_DESC *GetLayoutLocation() const;
		int GetLayoutCount() const;

	private:
		std::vector<D3D11_INPUT_ELEMENT_DESC> myDescription;
		int myPerVertexCount;
		int myPerInstanceCount;
	};
}
