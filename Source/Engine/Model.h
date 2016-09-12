#pragma once

class GenericVertexBuffer;
class IndexBuffer;
struct SimpleVertex;

class Effect;
class Texture;

class GenericModel
{
public:
	GenericModel(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture);
	virtual ~GenericModel();

	void SetTexture(std::shared_ptr<Texture> aTexture);

	void Render();
	std::shared_ptr<Texture> GetTexture();

protected:
	void CreateModel(const void * aVertexData, int aVertexCount, int aVertexSizeInBytes, const unsigned int * aIndexData, int aIndexCount);

private:
	std::unique_ptr<GenericVertexBuffer> myVertexBuffer;
	std::unique_ptr<IndexBuffer> myIndexBuffer;

	int myVertexCount;
	int myIndexCount;
	std::shared_ptr<Effect> myEffect;
	std::shared_ptr<Texture> myTexture;
};

template<typename TVertex>
class Model : public GenericModel
{
public:
	Model(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture);
	Model(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture, const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount);
	Model(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture, const std::vector<TVertex> & aVertexData, const std::vector<int> & aIndexData);
	template <size_t TVertexCount, size_t TIndexCount>
	Model(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture, const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData);

	~Model();

	void CreateModel(const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount);
	void CreateModel(const std::vector<TVertex> & aVertexData, const std::vector<int> & aIndexData);
	template <size_t TVertexCount, size_t TIndexCount>
	void CreateModel(const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData);
};

template<typename TVertex>
Model<TVertex>::Model(std::shared_ptr<Effect> myEffect, std::shared_ptr<Texture> myTexture)
	: GenericModel(myEffect, myTexture)
{

}

template<typename TVertex>
Model<TVertex>::Model(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture, const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount)
	: GenericModel(aEffect, aTexture)
{
	GenericModel::CreateModel(aVertexData, aVertexCount, sizeof(TVertex), aIndexData, aIndexCount);
}

template<typename TVertex>
Model<TVertex>::Model(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture, const std::vector<TVertex> & aVertexData, const std::vector<int> & aIndexData)
	: Model(aEffect, aTexture, &aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()))
{
}

template<typename TVertex>
template <size_t TVertexCount, size_t TIndexCount>
Model<TVertex>::Model(std::shared_ptr<Effect> aEffect, std::shared_ptr<Texture> aTexture, const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData)
	: Model(aEffect, aTexture, &aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()))
{
}

template<typename TVertex>
void Model<TVertex>::CreateModel(const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount)
{
	GenericModel::CreateModel(aVertexData, aVertexCount, sizeof(TVertex), aIndexData, aIndexCount);
}

template<typename TVertex>
void Model<TVertex>::CreateModel(const std::vector<TVertex> & aVertexData, const std::vector<int> & aIndexData)
{
	CreateModel(&aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()));
}

template<typename TVertex>
template <size_t TVertexCount, size_t TIndexCount>
void Model<TVertex>::CreateModel(const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData)
{
	CreateModel(&aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()));
}

template<typename TVertex>
Model<TVertex>::~Model()
{
}
