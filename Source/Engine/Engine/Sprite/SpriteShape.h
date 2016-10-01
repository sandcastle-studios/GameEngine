#pragma once

namespace ENGINE_NAMESPACE
{
	struct SpriteVertex;
	template <typename T>
	class VertexBuffer;
	class IndexBuffer;

	class SpriteShape
	{
	public:
		virtual ~SpriteShape();

		void RenderInstanced(const int aInstanceCount);

	protected:
		SpriteShape();
		void CreateBuffers(const SpriteVertex * aVertices, const int aVertexCount, const unsigned int * aIndices, const int aIndexCount);

	private:
		std::unique_ptr<VertexBuffer<SpriteVertex>> myVertexBuffer;
		std::unique_ptr<IndexBuffer> myIndexBuffer;
	};
}
