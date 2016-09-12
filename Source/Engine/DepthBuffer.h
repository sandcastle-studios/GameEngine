#pragma once

struct ID3D11DepthStencilView;
struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;

class Texture;

class DepthBuffer
{
public:
	DepthBuffer(unsigned int aWidth, unsigned int aHeight);
	~DepthBuffer();

	void Bind();
	void Unbind();
	void Clear(UINT aFlags, FLOAT aDepth, UINT8 aStencilMask);

	std::shared_ptr<Texture> GetTexture();
	
private:
	ID3D11DepthStencilView * myDepthStencilView;
	ID3D11Texture2D * myDepthStencilBuffer;
	ID3D11ShaderResourceView * myResourceView;
	std::shared_ptr<Texture> myTexture;
};
