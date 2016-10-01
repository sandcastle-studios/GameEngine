#pragma once

struct ID3D11InputLayout;

namespace ENGINE_NAMESPACE
{
	class VertexShader;
	class PixelShader;
	class InputLayout;

	class Effect
	{
	public:
		Effect();
		~Effect();

		void AttachVertexShader(const std::string & aFileName, const char * aEntryPoint);
		void AttachPixelShader(const std::string & aFileName, const char * aEntryPoint);

		void Link(const InputLayout & aLayout);

		void Bind() const;

	private:
		VertexShader *myVertexShader;
		PixelShader * myPixelShader;

		bool myIsLinked;
		ID3D11InputLayout * myLayout;
	};
}
