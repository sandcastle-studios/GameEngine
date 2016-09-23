#include "stdafx.h"
#include "Engine\Model\ModelBatch.h"
/*#include "Engine\ModelInstance.h"
#include "Engine\VertexBuffer.h"
#include "Engine\Model.h"
#include "Engine\Mesh.h"

ModelBatch::ModelBatch(const std::vector<std::shared_ptr<ModelInstance>> & aModelInstanceCollection)
{
	if (aModelInstanceCollection.size() == 0)
	{
		Error("Can not create a ModelBatch from 0 model instances!");
	}

	myModel = aModelInstanceCollection[0]->GetModel();

	std::vector<Matrix44f> matrices;
	matrices.resize(aModelInstanceCollection.size());

	for (size_t i = 0; i < aModelInstanceCollection.size(); i++)
	{
		matrices[i] = aModelInstanceCollection[i]->GetMatrix();
	}

	myMatrixVertexBuffer = std::make_unique<VertexBuffer<Matrix44f>>(&matrices[0], static_cast<int>(matrices.size()));
}

ModelBatch::ModelBatch(std::shared_ptr<GenericMesh> aModel, std::vector<Matrix44f> & aMatrices)
{
	if (aMatrices.size() == 0)
	{
		Error("Can not create a ModelBatch from 0 matrices!");
	}

	myModel = aModel;
	myMatrixVertexBuffer = std::make_unique<VertexBuffer<Matrix44f>>(&aMatrices[0], static_cast<int>(aMatrices.size()));
}

void ModelBatch::Render()
{
	myMatrixVertexBuffer->Bind(1);
	myModel->RenderInstanced(myMatrixVertexBuffer->GetVertexCount());
}

ModelBatch::~ModelBatch()
{
}
*/