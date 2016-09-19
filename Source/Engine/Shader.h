#pragma once

struct ID3D10Blob;

class Shader : public Resource
{
public:
	~Shader();

	virtual void Bind() const;

protected:
	Shader(const std::string & aFilePath);

	ID3D10Blob * CreateShader(const std::string & aFileName, const char * aEntryPoint, const char * aCompileProfile);
};

