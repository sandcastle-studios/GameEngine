#pragma once

class GenericModel;
template<typename T>
class VertexBuffer;
class ModelInstance;

class ModelRenderer
{
public:
	ModelRenderer();
	~ModelRenderer();

	void Render(const ModelInstance & aModelInstance);
	void RenderBuffer();

private:
	std::shared_ptr<const GenericModel> myCurrentlyScheduledModel;

	std::vector<Matrix44f> myMatrices;
	int myMatrixCounter;

	std::vector<std::shared_ptr<VertexBuffer<Matrix44f>>> myVertexBuffers;

	bool isInBatch;
};

