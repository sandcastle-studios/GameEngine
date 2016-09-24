#pragma once
#include "Surface.h"

class GenericVertexBuffer;
class IndexBuffer;
struct SimpleVertex;

class Effect;
class Texture;

template<typename TVertex>
class Mesh;

class GenericMesh
{
public:
	virtual ~GenericMesh();

	void SetSurface(const Surface & aSurface);
	void SetEffect(const std::shared_ptr<Effect> & aEffect);

	void Render() const;
	void RenderInstanced(int aInstanceCount) const;

	const BoundingBoxf & GetBoundingBox();

	size_t GetIdentifier() const;
	
	void AssignIdentifier(size_t aIdentifier);
protected:
	void CreateMesh(const void * aVertexData, int aVertexCount, int aVertexSizeInBytes, const unsigned int * aIndexData, int aIndexCount);

private:
	// Only Mesh<TVertex> may inherit
	template<typename TVertex>
	friend class Mesh;
	GenericMesh(const std::shared_ptr<Effect> & aEffect, const Surface & aSurface);
	std::unique_ptr<GenericVertexBuffer> myVertexBuffer;
	std::unique_ptr<IndexBuffer> myIndexBuffer;

	int myVertexCount;
	int myIndexCount;
	Surface mySurface;
	BoundingBoxf myBoundingBox;
	size_t myIdentifier;

	std::shared_ptr<Effect> myEffect;
};

template<typename TVertex>
class Mesh : public GenericMesh
{
public:
	Mesh(const std::shared_ptr<Effect> & aEffect, const Surface & aSurface);
	Mesh(const std::shared_ptr<Effect> & aEffect, const Surface & aSurface, const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount);
	Mesh(const std::shared_ptr<Effect> & aEffect, const Surface & aSurface, const std::vector<TVertex> & aVertexData, const std::vector<unsigned int> & aIndexData);
	template <size_t TVertexCount, size_t TIndexCount>
	Mesh(const std::shared_ptr<Effect> & aEffect, const Surface & aSurface, const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData);

	~Mesh();

	void CreateMesh(const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount);
	void CreateMesh(const std::vector<TVertex> & aVertexData, const std::vector<unsigned int> & aIndexData);
	template <size_t TVertexCount, size_t TIndexCount>
	void CreateMesh(const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData);
};

template<typename TVertex>
Mesh<TVertex>::Mesh(const std::shared_ptr<Effect> & aEffect, const Surface & aSurface)
	: GenericMesh(aEffect, aSurface)
{

}

template<typename TVertex>
Mesh<TVertex>::Mesh(const std::shared_ptr<Effect> & aEffect, const Surface & aSurface, const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount)
	: GenericMesh(aEffect, aSurface)
{
	CreateMesh(aVertexData, aVertexCount, aIndexData, aIndexCount);
}

template<typename TVertex>
Mesh<TVertex>::Mesh(const std::shared_ptr<Effect> & aEffect, const Surface & aSurface, const std::vector<TVertex> & aVertexData, const std::vector<unsigned int> & aIndexData)
	: Mesh(aEffect, aSurface, &aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()))
{
}

template<typename TVertex>
template <size_t TVertexCount, size_t TIndexCount>
Mesh<TVertex>::Mesh(const std::shared_ptr<Effect> & aEffect, const Surface & aSurface, const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData)
	: Mesh(aEffect, aSurface, &aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()))
{
}

template<typename TVertex>
void Mesh<TVertex>::CreateMesh(const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount)
{
	GenericMesh::CreateMesh(aVertexData, aVertexCount, sizeof(TVertex), aIndexData, aIndexCount);

	if (aVertexCount > 0)
	{
		BoundingBoxf bb(aVertexData[0].GetPosition());
		for (int i = 1; i < aVertexCount; i++)
		{
			bb.ExpandToContain(aVertexData[i].GetPosition());
		}
		myBoundingBox = bb;
	}
}

template<typename TVertex>
void Mesh<TVertex>::CreateMesh(const std::vector<TVertex> & aVertexData, const std::vector<unsigned int> & aIndexData)
{
	CreateMesh(&aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()));
}

template<typename TVertex>
template <size_t TVertexCount, size_t TIndexCount>
void Mesh<TVertex>::CreateMesh(const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData)
{
	CreateMesh(&aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()));
}

template<typename TVertex>
Mesh<TVertex>::~Mesh()
{
}
