#pragma once

struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;

class Texture
{
public:
	Texture(unsigned int aWidth, unsigned int aHeight, bool aIsRenderTarget = false);
	Texture(const wchar_t * aPath);
	Texture(const std::wstring & aPath);
	Texture(const char * aPath);
	Texture(const std::string & aPath);
	Texture(ID3D11Texture2D * aTexture, ID3D11ShaderResourceView * aResourceView, int aWidth, int aHeight);
	~Texture();

	void BindToVS(int aSlot);
	void BindToPS(int aSlot);
	void BindToGS(int aSlot);
	void BindToCS(int aSlot);
	void BindToHS(int aSlot);
	void BindToDS(int aSlot);

	ID3D11Texture2D * GetTexture();

private:
	ID3D11Texture2D * myTexture;
	ID3D11ShaderResourceView * myTextureView;
	int myWidth;
	int myHeight;
public:
	void ReleaseResources();
};

