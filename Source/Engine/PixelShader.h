#pragma once
#include "Shader.h"

struct ID3D11PixelShader;

class PixelShader : public Shader
{
public:
	PixelShader(const char * aFileName, const char * aEntryPoint);
	~PixelShader();

	virtual void Bind() const override;

private:
	ID3D11PixelShader * myShader;
};

