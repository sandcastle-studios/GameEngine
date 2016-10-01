#include "stdafx.h"
#include "Engine\Texture\TextureCube.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\DXHelpers\DDSTextureLoader.h"
#include "Engine\DXHelpers\dds.h"

namespace ENGINE_NAMESPACE
{
	TextureCube::TextureCube(const std::string & aPath)
		: Resource(aPath)
	{
		myTextureView = nullptr;
		Reload();
	}

	TextureCube::~TextureCube()
	{
		SAFE_RELEASE(myTextureView);
	}

	void TextureCube::BindToVS(int aSlot) const
	{
		Engine::GetInstance().GetRenderer().GetContext()->VSSetShaderResources(aSlot, 1, &myTextureView);
	}

	void TextureCube::BindToPS(int aSlot) const
	{
		Engine::GetInstance().GetRenderer().GetContext()->PSSetShaderResources(aSlot, 1, &myTextureView);
	}

	void TextureCube::BindToGS(int aSlot) const
	{
		Engine::GetInstance().GetRenderer().GetContext()->GSSetShaderResources(aSlot, 1, &myTextureView);
	}

	void TextureCube::BindToCS(int aSlot) const
	{
		Engine::GetInstance().GetRenderer().GetContext()->CSSetShaderResources(aSlot, 1, &myTextureView);
	}

	void TextureCube::BindToHS(int aSlot) const
	{
		Engine::GetInstance().GetRenderer().GetContext()->HSSetShaderResources(aSlot, 1, &myTextureView);
	}

	void TextureCube::BindToDS(int aSlot) const
	{
		Engine::GetInstance().GetRenderer().GetContext()->DSSetShaderResources(aSlot, 1, &myTextureView);
	}

	void TextureCube::Reload()
	{
		SAFE_RELEASE(myTextureView);

		DirectX::DDS_HEADER header;

		const std::string & path = GetPath();

		ID3D11Resource * texture;
		CheckDXError(
			DirectX::CreateDDSTextureFromFile(Engine::GetInstance().GetRenderer().GetDevice(), std::wstring(path.begin(), path.end()).c_str(), &texture, &myTextureView, &header)
		);

		myMipMapLevels = header.mipMapCount;

		SAFE_RELEASE(texture);
	}

	int TextureCube::GetMipMapLevels() const
	{
		return myMipMapLevels;
	}
}
