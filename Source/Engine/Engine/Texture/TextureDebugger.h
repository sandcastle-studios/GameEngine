#pragma once

class Texture;

class TextureDebugger
{
public:
	TextureDebugger();
	~TextureDebugger();

	void Render();

	void QueueRender(std::shared_ptr<Texture> aTextureToView);

private:
	std::vector<std::shared_ptr<Texture>> myTexturesToDebug;
	Sprite mySprite;
};

