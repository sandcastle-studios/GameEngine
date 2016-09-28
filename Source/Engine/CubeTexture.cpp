#include "stdafx.h"
#include "CubeTexture.h"
#include "DXRenderer.h"
#include "DDSTextureLoader.h"
#include "dds.h"

CubeTexture::CubeTexture(const std::string & aPath)
	: Resource(aPath)
{
	myTextureView = nullptr;
	Reload();
}

CubeTexture::~CubeTexture()
{
	SAFE_RELEASE(myTextureView);
}

void CubeTexture::BindToVS(int aSlot) const
{
	Engine::GetInstance().GetRenderer().GetContext()->VSSetShaderResources(aSlot, 1, &myTextureView);
}

void CubeTexture::BindToPS(int aSlot) const
{
	Engine::GetInstance().GetRenderer().GetContext()->PSSetShaderResources(aSlot, 1, &myTextureView);
}

void CubeTexture::BindToGS(int aSlot) const
{
	Engine::GetInstance().GetRenderer().GetContext()->GSSetShaderResources(aSlot, 1, &myTextureView);
}

void CubeTexture::BindToCS(int aSlot) const
{
	Engine::GetInstance().GetRenderer().GetContext()->CSSetShaderResources(aSlot, 1, &myTextureView);
}

void CubeTexture::BindToHS(int aSlot) const
{
	Engine::GetInstance().GetRenderer().GetContext()->HSSetShaderResources(aSlot, 1, &myTextureView);
}

void CubeTexture::BindToDS(int aSlot) const
{
	Engine::GetInstance().GetRenderer().GetContext()->DSSetShaderResources(aSlot, 1, &myTextureView);
}

void CubeTexture::Reload()
{
	SAFE_RELEASE(myTextureView);

	DirectX::DDS_HEADER header;

	const std::string & path = GetPath();

	ID3D11Resource * texture;
	CheckDXError(
		DirectX::CreateDDSTextureFromFile(Engine::GetInstance().GetRenderer().GetDevice(), std::wstring(path.begin(), path.end()).c_str(), &texture, &myTextureView, &header)
	);

	myMipMapCount = header.mipMapCount;

	SAFE_RELEASE(texture);
}

unsigned int CubeTexture::GetMipMapCount() const
{
	return myMipMapCount;
}

