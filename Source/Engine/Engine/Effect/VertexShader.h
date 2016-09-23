#pragma once
#include "Engine\Effect\Shader.h"

struct ID3D11VertexShader;
struct ID3D11InputLayout;
class InputLayout;

class VertexShader : public Shader
{
public:
	VertexShader(const std::string & aFileName, const char * aEntryPoint);
	~VertexShader();
	
	void Bind() const override;
	void Reload() override;

	ID3D11InputLayout * CreateLayout(const InputLayout & aLayoutDescription);

private:
	std::string myEntryPoint;
	ID3D11VertexShader * myShader;
	ID3D10Blob * myBlob;
};

