#include "stdafx.h"
#include "Shader.h"
#include <d3d11.h>
#include <d3dcompiler.h>

Shader::Shader()
{
}

ID3D10Blob * Shader::CreateShader(const char * aFileName, const char * aEntryPoint, const char * aCompileProfile)
{
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
	flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	LPCSTR profile = aCompileProfile;
	const D3D_SHADER_MACRO defines[] =
	{
		NULL, NULL
	};

	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* shaderBlob = nullptr;

	std::string filename(aFileName);

	HRESULT hr = D3DCompileFromFile(std::wstring(filename.begin(), filename.end()).c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		aEntryPoint, profile,
		flags, 0, &shaderBlob, &errorBlob);

	if (FAILED(hr) == true)
	{
		if (errorBlob)
		{
			std::cout << static_cast<char*>(errorBlob->GetBufferPointer()) << std::endl;
			errorBlob->Release();
			errorBlob = nullptr;
		}

		if (shaderBlob)
		{
			shaderBlob->Release();
			shaderBlob = nullptr;
		}

		abort();
	}

	return shaderBlob;
}

Shader::~Shader()
{
}
