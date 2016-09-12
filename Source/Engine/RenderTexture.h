#pragma once

struct ID3D11RenderTargetView;
class Texture;

class RenderTexture
{
public:
	RenderTexture(unsigned int aWidth, unsigned int aHeight);
	RenderTexture(ID3D11RenderTargetView * aRenderTarget);
	~RenderTexture();

	void Bind(int aSlot);

	std::shared_ptr<Texture> GetTexture();

private:
	std::shared_ptr<Texture> myTexture;
	ID3D11RenderTargetView * myRenderTargetView;
};

