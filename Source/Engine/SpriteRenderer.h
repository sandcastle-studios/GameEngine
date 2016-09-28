#pragma once

class Texture;
struct SpriteVertex;
class Model;
class Effect;
class GenericMesh;

class SpriteRenderer
{
public:
	SpriteRenderer();
	void RenderWholeTexture(std::shared_ptr<Texture> aTexture, const Vector2f &aTopLeft, const Vector2f &aSize);
	~SpriteRenderer();

private:
	std::shared_ptr<Effect> myEffect;
	std::unique_ptr<Model> myUnitModel;
	std::shared_ptr<GenericMesh> myUnitMesh;
};

