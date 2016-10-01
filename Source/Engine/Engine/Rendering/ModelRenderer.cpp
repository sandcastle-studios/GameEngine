#include "stdafx.h"
#include "Engine\Rendering\ModelRenderer.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "Engine\Model\ModelInstance.h"
#include "Engine\Model\Model.h"
#include "Engine\Model\Mesh.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Buffer\ConstantBuffer.h"
#include "..\Texture\TextureCube.h"
#include <Engine\Effect\StandardEffect.h>

namespace ENGINE_NAMESPACE
{

	ModelRenderer::ModelRenderer()
	{
		// Reserve identifier 0
		myMeshes.push_back(nullptr);
		myIsInstantRendering = false;

		myVertexBuffers.push_back(std::make_shared<VertexBuffer<Matrix44f>>(nullptr, 1, false));
		myLightingBuffer = std::make_shared<ConstantBuffer<LightConstantBufferData>>();

		myLightingData.directionLight[0].color = Vector4f(1.f, 1.f, 1.f, 1.f);
		myLightingData.directionLight[0].direction = Vector4f(Vector3f(-1.f, -1.f, 1.f).GetNormalized(), 1.f);

		mySkybox = std::make_shared<TextureCube>("textures/cubeMap.dds");
		myLightingData.myCubeMapMipMaps = mySkybox->GetMipMapLevels();

		myEffect = std::make_shared<StandardEffect>();
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

	void ModelRenderer::Render(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<GenericMesh> & aMesh, const Matrix44f & aMatrix)
	{
		size_t identifier = aMesh->GetIdentifier();
		if (identifier == 0)
		{
			identifier = GenerateBatchIdentifier(aMesh);
			aMesh->AssignIdentifier(identifier);
		}

		myMeshes[identifier]->AddInstance(aEffect == nullptr ? myEffect : aEffect, aMatrix);
	}

	void ModelRenderer::RenderBuffer()
	{
		myIsInstantRendering = false;
		mySkybox->BindToPS(6);

		UpdateAndBindLightingBuffer();

		for (size_t i = 0; i < myCurrentlyScheduledBatches.size(); i++)
		{
			auto && matricesContainers = myCurrentlyScheduledBatches[i]->GetMatricesContainers();

			for (unsigned short  j = 0; j < matricesContainers.Size(); j++)
			{
				if (matricesContainers[j].effect == nullptr)
				{
					break;
				}

				const Matrix44f * matrices = &matricesContainers[j].matrices[0];
				unsigned short matricesCount = matricesContainers[j].matrixCounter;

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
				myCurrentlyScheduledBatches[i]->GetMesh().RenderInstanced(matricesContainers[j].effect, matricesCount);
			}

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

	void ModelRenderer::InstantRender(const std::shared_ptr<Effect>& aEffect, const std::shared_ptr<GenericMesh> & myMesh)
	{
		if (myIsInstantRendering == false)
		{
			Error("Instant rendering must be preceeded by calling ModelRenderer::PrepareInstantRender()");
		}

		myMesh->RenderInstanced(aEffect, 1);
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
		myMatrices.Resize(2);
		for (unsigned short i = 0; i < myMatrices.Size(); i++)
		{
			myMatrices[i].matrices.Resize(16);
			myMatrices[i].matrixCounter = 0;
		}
		myEffectCounter = 0;
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

	void BatchEntry::AddInstance(const std::shared_ptr<Effect> & aEffect, const Matrix44f & aMatrix)
	{
		if (myEffectCounter + 1 >= static_cast<int>(myMatrices.Size()))
		{
			unsigned short oldSize = myMatrices.Size();
			myMatrices.Resize(oldSize * 2);
			for (unsigned short i = oldSize; i < myMatrices.Size(); i++)
			{
				myMatrices[i].matrices.Resize(16);
				myMatrices[i].matrixCounter = 0;
			}
		}

		unsigned short effectIndex = static_cast<unsigned short>(myEffectCounter);

		for (short i = static_cast<short>(myEffectCounter) - 1; i >= 0; i--)
		{
			if (myMatrices[i].effect == aEffect)
			{
				effectIndex = static_cast<unsigned short>(i);
				return;
			}
		}

		auto && data = myMatrices[effectIndex];

		if (data.matrixCounter + 1 >= static_cast<int>(data.matrices.Size()))
		{
			data.matrices.Resize(static_cast<unsigned short>(data.matrices.Size() * 2));
		}

		data.matrices[data.matrixCounter++] = aMatrix;

		if (data.effect == nullptr)
		{
			data.effect = aEffect;
		}

		Schedule();
	}

	void BatchEntry::FinishedRendering()
	{
		for (unsigned short i = 0; i < myMatrices.Size(); i++)
		{
			if (myMatrices[i].effect == nullptr)
			{
				break;
			}

			myMatrices[i].effect = nullptr;
			myMatrices[i].matrixCounter = 0;
		}

		myEffectCounter = 0;
		myMeshScheduleLock = nullptr;
	}

	const GrowingArray<BatchEntry::MatricesContainer> & BatchEntry::GetMatricesContainers() const
	{
		return myMatrices;
	}

	const GenericMesh & BatchEntry::GetMesh() const
	{
		if (myMeshScheduleLock == nullptr)
		{
			Error("Can only get the mesh of a scheduled batch entry!");
		}
		return *myMeshScheduleLock;
	}
}

