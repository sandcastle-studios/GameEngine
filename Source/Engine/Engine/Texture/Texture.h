#pragma once

struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;

class Texture : public Resource
{
public:
	Texture(unsigned int aWidth, unsigned int aHeight, bool aIsRenderTarget = false);
	Texture(const std::string & aPath);
	Texture(ID3D11Texture2D * aTexture, ID3D11ShaderResourceView * aResourceView, int aWidth, int aHeight);
	~Texture();

	void BindToVS(int aSlot) const;
	void BindToPS(int aSlot) const;
	void BindToGS(int aSlot) const;
	void BindToCS(int aSlot) const;
	void BindToHS(int aSlot) const;
	void BindToDS(int aSlot) const;

	ID3D11Texture2D * GetTexture();

	void Reload() override;

	Vector2f GetSize() const;

private:
	ID3D11Texture2D * myTexture;
	ID3D11ShaderResourceView * myTextureView;
	int myWidth;
	int myHeight;
};

inline Vector2f Texture::GetSize() const
{
	return Vector2f(static_cast<float>(myWidth), static_cast<float>(myHeight));
}
