#pragma once

struct ID3D11DepthStencilView;
struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;
struct ID3D11RenderTargetView;

class Texture;

class DepthBuffer
{
public:
	DepthBuffer(unsigned int aWidth, unsigned int aHeight);
	~DepthBuffer();

	void Bind();
	void Unbind();

	void Clear();
	void Clear(UINT aFlags, FLOAT aDepth, UINT8 aStencilMask);

	std::shared_ptr<Texture> GetTexture();
	ID3D11DepthStencilView * GetView();
	
private:
	ID3D11DepthStencilView * myDepthStencilView;
	ID3D11Texture2D * myDepthStencilBuffer;
	ID3D11ShaderResourceView * myResourceView;
	std::shared_ptr<Texture> myTexture;
};
