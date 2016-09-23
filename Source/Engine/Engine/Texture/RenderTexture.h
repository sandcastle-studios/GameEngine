#pragma once
struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;
class Texture;
class DepthBuffer;

class RenderTexture
{
public:
	RenderTexture(unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer);
	RenderTexture(ID3D11Texture2D * aTexture, ID3D11RenderTargetView * aRenderTarget, ID3D11ShaderResourceView * aShaderResourceView, unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer);
	~RenderTexture();

	void Bind(int aSlot, bool aUpdateViewport = true);

	void Clear(const Vector4f & aColor);

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;

	const std::shared_ptr<Texture> & GetTexture();

	const std::shared_ptr<DepthBuffer> & GetDepthBuffer();
	std::shared_ptr<const DepthBuffer> GetDepthBuffer() const;

private:
	std::shared_ptr<Texture> myTexture;
	std::shared_ptr<DepthBuffer> myDepthBuffer;
	ID3D11RenderTargetView * myRenderTargetView;
	unsigned int myWidth;
	unsigned int myHeight;
};

