#include "stdafx.h"
#include "Engine\Rendering\ModelRenderer.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "Engine\Model\ModelInstance.h"
#include "Engine\Model\Model.h"
#include "Engine\Model\Mesh.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Buffer\ConstantBuffer.h"
#include "..\Texture\TextureCube.h"

ModelRenderer::ModelRenderer()
{
	// Reserve identifier 0
	myMeshes.push_back(nullptr);
	myIsInstantRendering = false;

	myVertexBuffers.push_back(std::make_shared<VertexBuffer<Matrix44f>>(nullptr, 1, false));
	myLightingBuffer = std::make_shared<ConstantBuffer<LightConstantBufferData>>();
	
	myLightingData.directionLight[0].color = Vector4f(1.f, 1.f, 1.f, 1.f);
	myLightingData.directionLight[0].direction = Vector4f(Vector3f(-1.f, -1.f, 1.f).GetNormalized(), 1.f);

	mySkybox = std::make_shared<TextureCube>("textures/skansen.dds");
	myLightingData.myCubeMapMipMaps = mySkybox->GetMipMapLevels();
}

ModelRenderer::~ModelRenderer()
{
	// Empty rendering schedule hopefully releasing any shared pointers that are left to meshes
	for (size_t i = 0; i < myCurrentlyScheduledBatches.size(); i++)
	{
		myCurrentlyScheduledBatches[i]->FinishedRendering();
	}
	
	for (size_t i = 0; i < myMeshes.size(); i++)
	{
		if (myMeshes[i] != nullptr)
		{
			Error("A mesh's destructor was never invoked!\nMemory was leaked!");
		}
	}
}

void ModelRenderer::Render(const std::shared_ptr<GenericMesh> & aMesh, const Matrix44f & aMatrix)
{
	size_t identifier = aMesh->GetIdentifier();
	if (identifier == 0)
	{
		identifier = GenerateBatchIdentifier(aMesh);
		aMesh->AssignIdentifier(identifier);
	}

	myMeshes[identifier]->AddInstance(aMatrix);
}

void ModelRenderer::RenderBuffer()
{
	myIsInstantRendering = false;
	mySkybox->BindToPS(6);

	UpdateAndBindLightingBuffer();

	for (size_t i=0; i<myCurrentlyScheduledBatches.size(); i++)
	{
		const Matrix44f * matrices = myCurrentlyScheduledBatches[i]->GetInstances();
		int matricesCount = myCurrentlyScheduledBatches[i]->GetInstanceCount();

		auto vertexBuffer = myVertexBuffers[0];

		int c = 0;
		while (matricesCount >= vertexBuffer->GetCount())
		{
			c++;
			
			if (c >= static_cast<int>(myVertexBuffers.size()))
			{
				myVertexBuffers.push_back(std::make_shared<VertexBuffer<Matrix44f>>(nullptr, myVertexBuffers.back()->GetCount() * 2, false));
			}

			vertexBuffer = myVertexBuffers[c];
		}

		vertexBuffer->UpdateData(matrices, matricesCount, false);
		vertexBuffer->Bind(1);
		myCurrentlyScheduledBatches[i]->GetMesh().RenderInstanced(matricesCount);

		myCurrentlyScheduledBatches[i]->FinishedRendering();
	}

	myCurrentlyScheduledBatches.clear();
}

void ModelRenderer::Schedule(BatchEntry & aBatch)
{
	myCurrentlyScheduledBatches.push_back(&aBatch);
}

size_t ModelRenderer::GenerateBatchIdentifier(const std::shared_ptr<GenericMesh> & aMesh)
{
	size_t id;

	if (myReturnedBatchIdentifiers.size() > 0)
	{
		id = myReturnedBatchIdentifiers.top();
		myReturnedBatchIdentifiers.pop();
	}
	else
	{
		id = myMeshes.size();
		myMeshes.push_back(nullptr);
	}

	myMeshes[id] = std::make_unique<BatchEntry>(aMesh);

	return id;
}

void ModelRenderer::ReturnBatchIdentifier(size_t aBatchIdentifier)
{
	myMeshes[aBatchIdentifier] = nullptr;

	myReturnedBatchIdentifiers.push(aBatchIdentifier);
}

void ModelRenderer::SetAmbient(float aAmbient)
{
	myLightingData.ambient = aAmbient;
}

void ModelRenderer::SetDirectionalLight(int aIndex, const Vector3f & aLightDirection, const Vector4f & aLightColor)
{
	myLightingData.directionLight[aIndex].direction = Vector4f(aLightDirection.GetNormalized(), 1.f);
	myLightingData.directionLight[aIndex].color = aLightColor;
}

float ModelRenderer::GetAmbient() const
{
	return myLightingData.ambient;
}

void ModelRenderer::UpdateAndBindLightingBuffer()
{
	myLightingBuffer->UpdateData(myLightingData);
	myLightingBuffer->BindToPS(1);
}

void ModelRenderer::InstantRender(const std::shared_ptr<GenericMesh> & myMesh)
{
	if (myIsInstantRendering == false)
	{
		Error("Instant rendering must be preceeded by calling ModelRenderer::PrepareInstantRender()");
	}

	myMesh->RenderInstanced(1);
}

void ModelRenderer::PrepareInstantRender(const Matrix44f & aWorldMatrix)
{
	myIsInstantRendering = true;

	myVertexBuffers[0]->UpdateData(&aWorldMatrix, 1, false);
	myVertexBuffers[0]->Bind(1);

	UpdateAndBindLightingBuffer();
}

BatchEntry::BatchEntry(const std::shared_ptr<const GenericMesh> & aMesh)
{
	myMesh = aMesh;
	myMeshScheduleLock = nullptr;
	myMatrices.resize(4);
}

void BatchEntry::Schedule()
{
	if (myMeshScheduleLock)
	{
		return;
	}
	myMeshScheduleLock = myMesh.lock();

	Engine::GetInstance().GetRenderer().GetModelRenderer().Schedule(*this);
}

bool BatchEntry::IsScheduled()
{
	return myMeshScheduleLock != nullptr;
}

void BatchEntry::AddInstance(const Matrix44f & aMatrix)
{
	if (myMatrixCounter + 1 >= static_cast<int>(myMatrices.size()))
	{
		myMatrices.resize(myMatrices.size() * 2);
	}

	myMatrices[myMatrixCounter++] = aMatrix;

	Schedule();
}

const Matrix44f * BatchEntry::GetInstances() const
{
	return &myMatrices[0];
}

int BatchEntry::GetInstanceCount() const
{
	return myMatrixCounter;
}

void BatchEntry::FinishedRendering()
{
	myMatrixCounter = 0;
	myMeshScheduleLock = nullptr;
}

const GenericMesh & BatchEntry::GetMesh() const
{
	if (myMeshScheduleLock == nullptr)
	{
		Error("Can only get the mesh of a scheduled batch entry!");
	}
	return *myMeshScheduleLock;
}
