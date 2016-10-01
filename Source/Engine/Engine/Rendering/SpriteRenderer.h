#pragma once

namespace ENGINE_NAMESPACE
{

	class SpriteEffect;
	class QuadSpriteShape;
	class Sprite;

	template<typename T>
	class VertexBuffer;

	struct SpriteInstanceData
	{
		Matrix44f toWorld;
		Vector4f color;
	};


	class SpriteRenderer
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Render(const Sprite &aSprite);

	private:
		std::shared_ptr<SpriteEffect> mySpriteEffect;
		std::unique_ptr<VertexBuffer<SpriteInstanceData>> myInstanceBuffer;
		std::unique_ptr<QuadSpriteShape> myQuad;
	};

}
