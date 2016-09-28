#pragma once

struct ID3D11ShaderResourceView;

class TextureCube : public Resource
{
public:
	TextureCube(const std::string & aPath);
	~TextureCube();

	void BindToVS(int aSlot) const;
	void BindToPS(int aSlot) const;
	void BindToGS(int aSlot) const;
	void BindToCS(int aSlot) const;
	void BindToHS(int aSlot) const;
	void BindToDS(int aSlot) const;

	void Reload() override;

private:
	ID3D11ShaderResourceView * myTextureView;
};
