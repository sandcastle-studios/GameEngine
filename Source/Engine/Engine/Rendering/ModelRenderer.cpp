#include "stdafx.h"
#include "Engine\Rendering\ModelRenderer.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "Engine\Model\ModelInstance.h"
#include "Engine\Model\Model.h"
#include "Engine\Model\Mesh.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Buffer\ConstantBuffer.h"
#include "Engine\Effect\StandardEffect.h"
#include "Engine\Texture\MultiRenderTexture.h"
#include "Engine\Model\AssimpModel.h"
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Effect\Effect.h"
#include "..\RenderingConfiguration\BlendState.h"
#include <Engine/Sprite/SpriteEffect.h>
#include <imgui.h>

ModelRenderer::ModelRenderer()
{
	// Reserve identifier 0
	myMeshes.push_back(nullptr);
	myIsInstantRendering = false;

	myVertexBuffers.push_back(std::make_shared<VertexBuffer<Matrix44f>>(nullptr, 1, false));
	myLightingBuffer = std::make_shared<ConstantBuffer<LightConstantBufferData>>();

	myEffect = std::make_shared<StandardEffect>();

	myPointLightBuffer = std::make_shared<ConstantBuffer<PointLight>>();
	myDeferredTextures = std::make_shared<MultiRenderTexture>(3, 1280, 720, true);
	// myLambertBuffer = std::make_shared<RenderTexture>(1280, 720, false);

	myLambertEffect = std::make_shared<Effect>();
	myLambertEffect->AttachVertexShader("shaders/lambert.fx", "VShader");
	myLambertEffect->AttachPixelShader("shaders/lambert.fx", "PShader");

	InputLayout layout;
	layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("BITANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT);

	layout.AddPerInstance("INSTANCE_MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);

	myLambertEffect->Link(layout);

	myLightModels.push_back(std::make_shared<AssimpModel>(nullptr, "models/lightspheres/lightsphere_1.fbx"));
	myLightModelsMinDistances.push_back(7.0f);
	myLightModels.push_back(std::make_shared<AssimpModel>(nullptr, "models/lightspheres/lightsphere_2.fbx"));
	myLightModelsMinDistances.push_back(6.0f);
	myLightModels.push_back(std::make_shared<AssimpModel>(nullptr, "models/lightspheres/lightsphere_3.fbx"));
	myLightModelsMinDistances.push_back(5.0f);
	myLightModels.push_back(std::make_shared<AssimpModel>(nullptr, "models/lightspheres/lightsphere_4.fbx"));
	myLightModelsMinDistances.push_back(4.0f);
	myLightModels.push_back(std::make_shared<AssimpModel>(nullptr, "models/lightspheres/lightsphere_5.fbx"));
	myLightModelsMinDistances.push_back(2.0f);

	memset(&myLightingData, 0, sizeof(myLightingData));

	myLightingData.directionLight[0].color = Vector4f(1.f, 1.f, 1.f, 1.f);
	myLightingData.directionLight[0].direction = Vector4f(Vector3f(-1.f, -1.f, 1.f).GetNormalized(), 1.f);
	
	/*
	myLambertRenderingEffect = std::make_shared<SpriteEffect>("shaders/lambert_render.fx", "VShader", "shaders/lambert_render.fx", "PShader");
	myFullscreenQuad.SetPosition(Vector2f::Zero);
	myFullscreenQuad.SetEffect(myLambertRenderingEffect);
	*/
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
		
		myEffect->Bind();
		
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

void ModelRenderer::SetDirectionalLight(int aIndex, const Vector3f & aLightDirection, const Vector4f & aLightColor)
{
	myLightingData.directionLight[aIndex].direction = Vector4f(aLightDirection.GetNormalized(), 1.f);
	myLightingData.directionLight[aIndex].color = aLightColor;
}

void ModelRenderer::SetPointLight(int aIndex, const Vector3f & aLightPosition, const Vector3f & aLightColor, const float aLightRadius, const float aLightIntensity)
{
	myLightingData.pointLight[aIndex].position = aLightPosition;
	myLightingData.pointLight[aIndex].radius = aLightRadius;
	myLightingData.pointLight[aIndex].color = aLightColor;
	myLightingData.pointLight[aIndex].intensity = aLightIntensity;
}

const LightConstantBufferData & ModelRenderer::GetLightData() const
{
	return myLightingData;
}

const std::shared_ptr<MultiRenderTexture> & ModelRenderer::GetDeferredTexture() const
{
	return myDeferredTextures;
}

/*const std::shared_ptr<RenderTexture> & ModelRenderer::GetLambertTexture() const
{
	return myLambertBuffer;
}*/

void ModelRenderer::UpdateAndBindLightingBuffer()
{
	myLightingBuffer->UpdateData(myLightingData);
	myLightingBuffer->BindToPS(1);
}

void ModelRenderer::RenderLights()
{
	myDeferredTextures->Bind();
	RenderBuffer();
	// myLambertBuffer->Bind(0, false);
	Engine::GetRenderer().GetBackBuffer()->Bind(0);
	myLambertEffect->Bind();
	Engine::GetRenderer().GetAdditiveBlendState()->Bind();
	Engine::GetRenderer().DisableDepthWrite();

	myDeferredTextures->GetDepthBuffer()->Bind();
	
	myDeferredTextures->GetRenderTextures()[0]->GetTexture()->BindToPS(0);
	myDeferredTextures->GetRenderTextures()[1]->GetTexture()->BindToPS(1);
	myDeferredTextures->GetRenderTextures()[2]->GetTexture()->BindToPS(2);

	myPointLightBuffer->BindToPS(2);

	for (size_t i = 0; i < 8; i++)
	{
		auto &&lightData = myLightingData.pointLight[i];
		
		if (lightData.intensity == 0.f)
		{
			continue;
		}

		myPointLightBuffer->UpdateData(lightData);

		ModelInstance inst(nullptr);

		float distance = (lightData.position - myCameraPosition).Length();

		for (int j=0; j<myLightModels.size(); j++)
		{
			if (distance > myLightModelsMinDistances[j] * lightData.radius)
			{
				if (ImGui::Begin("Light Level", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(FormatString("Current Light LOD: {0}\nCurrent Distance: {1}", j, distance).c_str());
				}
				ImGui::End();
				inst = ModelInstance(myLightModels[j]);
				break;
			}
		}

		if (inst.GetModel() == nullptr)
		{
			// Fullscreen quad
		}
		else
		{
			Vector3f size = inst.GetBoundingBox().GetSize();

			inst.SetMatrix(Matrix44f::CreateScale(lightData.radius, lightData.radius, lightData.radius)
				* Matrix44f::CreateTranslation(lightData.position));

			inst.InstantRender();
		}
	}

	Engine::GetRenderer().GetAlphaBlendState()->Bind();
	/*Engine::GetRenderer().GetBackBuffer()->Bind(0);

	myDeferredTextures->GetRenderTextures()[0]->GetTexture()->BindToPS(0);
	myLambertBuffer->GetTexture()->BindToPS(1);

	myFullscreenQuad.SetScale(Engine::GetRenderer().GetRenderTargetResolution());
	myFullscreenQuad.Render();*/

	Engine::GetRenderer().EnableDepthWrite();
}

void ModelRenderer::SetCameraReferencePosition(const Vector3f& aCameraPosition)
{
	myCameraPosition = aCameraPosition;
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
