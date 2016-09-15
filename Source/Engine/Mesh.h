#pragma once

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

	void SetTexture(const std::shared_ptr<Texture> & aTexture);

	void Render() const;
	void RenderInstanced(int aInstanceCount) const;

	std::shared_ptr<Texture> GetTexture();

	const BoundingBoxf & GetBoundingBox();

	size_t GetIdentifier() const;
	
	void AssignIdentifier(size_t aIdentifier);
protected:
	void CreateMesh(const void * aVertexData, int aVertexCount, int aVertexSizeInBytes, const unsigned int * aIndexData, int aIndexCount);

private:
	// Only Mesh<TVertex> may inherit
	template<typename TVertex>
	friend class Mesh;
	GenericMesh(const std::shared_ptr<Texture> & aTexture);
	std::unique_ptr<GenericVertexBuffer> myVertexBuffer;
	std::unique_ptr<IndexBuffer> myIndexBuffer;

	int myVertexCount;
	int myIndexCount;
	std::shared_ptr<Texture> myTexture;
	BoundingBoxf myBoundingBox;
	size_t myIdentifier;

	// Model must be able to assign an effect to Mesh
	friend class Model;
	// Changing does not guarantee effect will be used for rendering, must be set through parent model
	std::shared_ptr<Effect> myEffect;
};

template<typename TVertex>
class Mesh : public GenericMesh
{
public:
	Mesh(const std::shared_ptr<Texture> & aTexture);
	Mesh(const std::shared_ptr<Texture> & aTexture, const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount);
	Mesh(const std::shared_ptr<Texture> & aTexture, const std::vector<TVertex> & aVertexData, const std::vector<unsigned int> & aIndexData);
	template <size_t TVertexCount, size_t TIndexCount>
	Mesh(const std::shared_ptr<Texture> & aTexture, const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData);

	~Mesh();

	void CreateMesh(const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount);
	void CreateMesh(const std::vector<TVertex> & aVertexData, const std::vector<unsigned int> & aIndexData);
	template <size_t TVertexCount, size_t TIndexCount>
	void CreateMesh(const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData);
};

template<typename TVertex>
Mesh<TVertex>::Mesh(const std::shared_ptr<Texture> & aTexture)
	: GenericMesh(myTexture)
{

}

template<typename TVertex>
Mesh<TVertex>::Mesh(const std::shared_ptr<Texture> & aTexture, const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount)
	: GenericMesh(aTexture)
{
	CreateMesh(aVertexData, aVertexCount, aIndexData, aIndexCount);
}

template<typename TVertex>
Mesh<TVertex>::Mesh(const std::shared_ptr<Texture> & aTexture, const std::vector<TVertex> & aVertexData, const std::vector<unsigned int> & aIndexData)
	: Mesh(aTexture, &aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()))
{
}

template<typename TVertex>
template <size_t TVertexCount, size_t TIndexCount>
Mesh<TVertex>::Mesh(const std::shared_ptr<Texture> & aTexture, const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData)
	: Mesh(aTexture, &aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()))
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
