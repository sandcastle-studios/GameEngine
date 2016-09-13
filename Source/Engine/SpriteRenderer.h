#pragma once

class Texture;
struct SpriteVertex;
template<typename T>
class Model;
class Effect;

class SpriteRenderer
{
public:
	SpriteRenderer();
	void RenderWholeTexture(std::shared_ptr<Texture> aTexture, const Vector2f &aTopLeft, const Vector2f &aSize);
	~SpriteRenderer();

private:
	std::shared_ptr<Effect> myEffect;
	std::unique_ptr<Model<SpriteVertex>> myUnitQuad;
};

