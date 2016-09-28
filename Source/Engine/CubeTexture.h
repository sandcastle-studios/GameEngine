#pragma once

struct ID3D11ShaderResourceView;

class CubeTexture : public Resource
{
public:
	CubeTexture(const std::string & aPath);
	~CubeTexture();

	void BindToVS(int aSlot) const;
	void BindToPS(int aSlot) const;
	void BindToGS(int aSlot) const;
	void BindToCS(int aSlot) const;
	void BindToHS(int aSlot) const;
	void BindToDS(int aSlot) const;

	void Reload() override;
	unsigned int GetMipMapCount() const;

private:
	ID3D11ShaderResourceView * myTextureView;
	unsigned int myMipMapCount;
};
