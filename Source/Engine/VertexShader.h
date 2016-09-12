#pragma once
#include "Shader.h"

struct ID3D11VertexShader;
struct ID3D11InputLayout;
class InputLayout;

class VertexShader : public Shader
{
public:
	VertexShader(const char * aFileName, const char * aEntryPoint);
	~VertexShader();
	
	virtual void Bind() const override;

	ID3D11InputLayout * CreateLayout(const InputLayout & aLayoutDescription);
private:
	ID3D11VertexShader * myShader;
	ID3D10Blob * myBlob;
};

