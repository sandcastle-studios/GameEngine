#pragma once

struct ID3D10Blob;

class Shader
{
public:
	~Shader();

	virtual void Bind() const = 0;

protected:
	Shader();

	ID3D10Blob * CreateShader(const char * aFileName, const char * aEntryPoint, const char * aCompileProfile);
};

