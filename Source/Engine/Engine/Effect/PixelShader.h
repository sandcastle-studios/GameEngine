#pragma once
#include "Engine\Effect\Shader.h"

struct ID3D11PixelShader;

namespace ENGINE_NAMESPACE
{
	class PixelShader : public Shader
	{
	public:
		PixelShader(const std::string & aFileName, const char * aEntryPoint);
		~PixelShader();

		void Bind() const override;
		void Reload() override;

	private:
		std::string myEntryPoint;
		ID3D11PixelShader * myShader;
	};
}
