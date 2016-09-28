#pragma once
#include "SpriteVertex.h"

class Effect;
class Texture;
class Model;

class TextureDebugger
{
public:
	TextureDebugger();
	~TextureDebugger();

	void Render();

	void QueueRender(std::shared_ptr<Texture> aTextureToView);

private:
	std::vector<std::shared_ptr<Texture>> myTexturesToDebug;
	std::shared_ptr<Effect> myEffect;
	std::unique_ptr<Model> myUnitQuad;
};

