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
	void RenderWholeTexture(std::shared_ptr<Texture> aTexture, const Vector2f &aTopLeft, const Vector2f &aSize, const std::shared_ptr<Effect> * aEffect = nullptr);
	~SpriteRenderer();

private:
	std::unique_ptr<Model> myUnitModel;
	std::shared_ptr<GenericMesh> myUnitMesh;
};

