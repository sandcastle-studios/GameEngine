#pragma once

class MultiRenderTexture
{
public:
	MultiRenderTexture(int aBufferCount, int aWidth, int aHeight, bool aGenerateDepthBuffer, bool isFloatingPoint[]);
	~MultiRenderTexture();

	void Bind();

	const std::vector<std::shared_ptr<RenderTexture>> & GetRenderTextures() const;
	const std::shared_ptr<DepthBuffer> & GetDepthBuffer() const;

	void Clear(const Vector4f & aColor = Vector4f(0.f, 0.f, 0.f, 0.f));
private:
	std::shared_ptr<DepthBuffer> myDepthBuffer;
	std::vector<std::shared_ptr<RenderTexture>> myRenderTextures;
	int myWidth;
	int myHeight;
};

