#include "stdafx.h"
#include "ModelRenderer.h"
#include "VertexBuffer.h"
#include "ModelInstance.h"
#include "Model.h"
#include "mesh.h"
#include "Stopwatch.h"

ModelRenderer::ModelRenderer()
{
	myMatrices.resize(256);
	myMatrixCounter = 0;

	myVertexBuffers.push_back(std::make_shared<VertexBuffer<Matrix44f>>(nullptr, 1, false));
}

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::Render(const ModelInstance & aModelInstance)
{
	myVertexBuffers[0]->UpdateData(&aModelInstance.GetMatrix(), 1, false);
	myVertexBuffers[0]->Bind(1);

	aModelInstance.GetModel()->Render();

	/*std::shared_ptr<const GenericModel> model = aModelInstance.GetModel();
	
	if (model != myCurrentlyScheduledModel)
	{
		RenderBuffer();
		myCurrentlyScheduledModel = model;
	}

	if (myMatrixCounter >= 1800)
	{
		RenderBuffer();
		myCurrentlyScheduledModel = model;
	}

	if (myMatrixCounter + 1 >= myMatrices.size())
		myMatrices.resize(myMatrices.size() * 2);

	myMatrices[myMatrixCounter++] = aModelInstance.GetMatrix();*/
}

void ModelRenderer::RenderBuffer()
{
	if (myCurrentlyScheduledModel == nullptr)
	{
		return;
	}

	if (myMatrixCounter > 0)
	{
		auto vertexBuffer = myVertexBuffers[0];

		int c = 0;
		while (myMatrixCounter >= vertexBuffer->GetVertexCount())
		{
			c++;
			
			if (c >= static_cast<int>(myVertexBuffers.size()))
			{
				myVertexBuffers.push_back(std::make_shared<VertexBuffer<Matrix44f>>(nullptr, myVertexBuffers.back()->GetVertexCount() * 2, false));
			}

			vertexBuffer = myVertexBuffers[c];
		}

		vertexBuffer->UpdateData(&myMatrices[0], myMatrixCounter, false);
		vertexBuffer->Bind(1);
		myCurrentlyScheduledModel->RenderInstanced(myMatrixCounter);
	}

	myMatrixCounter = 0;
	myCurrentlyScheduledModel = nullptr;
}
