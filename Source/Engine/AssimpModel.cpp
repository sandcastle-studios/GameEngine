#include "stdafx.h"
#include "AssimpModel.h"
#include <FBXLoader.h>
#include "Vertex.h"
#include "Texture.h"

AssimpModel::AssimpModel(const std::shared_ptr<Effect> & aEffect, const std::string & aFilePath)
	: Model(aEffect)
{
	myFinishedLoadingFlag.store(false);
	myPath = aFilePath;
	SetStatus(ModelStatus::eNotReady);
}

AssimpModel::~AssimpModel()
{
	if (GetStatus() == ModelStatus::ePreparing)
	{
		while (myFinishedLoadingFlag.load() == false)
		{
			Sleep(1);
		}
	}
}

bool AssimpModel::Prepare(bool aAsynchronous)
{
	if (GetStatus() == ModelStatus::eReady)
	{
		return true;
	}

	if (GetStatus() == ModelStatus::ePreparing)
	{
		if (myFinishedLoadingFlag.load() == true)
		{
			SetStatus(ModelStatus::eReady);
			return true;
		}
		return false;
	}

	if (aAsynchronous)
	{
		SetStatus(ModelStatus::ePreparing);
		Engine::GetThreadPool().QueueWorkItem(std::function<void()>([this] { this->LoadModel(); myFinishedLoadingFlag.store(true); }));
		return false;
	}
	else
	{
		LoadModel();
		SetStatus(ModelStatus::eReady);
		myFinishedLoadingFlag.store(true);
		return true;
	}
}

void AssimpModel::LoadModel()
{
	Stopwatch loadWatch;

	Engine::GetLogger().LogResource("Beginning to load model {0}", myPath);

	CFBXLoader loader;
	CLoaderModel * model = loader.LoadModel(myPath.c_str());

	std::string modelDirectory;
	size_t lastSlash = myPath.find_last_of("\\/");
	if (lastSlash == std::string::npos)
	{
		modelDirectory = "";
	}
	else
	{
		modelDirectory = myPath.substr(0, lastSlash + 1);
	}

	for (size_t i = 0; i < model->myMeshes.size(); i++)
	{
		CLoaderMesh * mesh = model->myMeshes[i];

		AddMesh(std::make_shared<AssimpMesh>(mesh, modelDirectory));
	}

	const int numTextures = 2;
	int indices[numTextures] = { 0, 5 };
	int slotIndices[numTextures] = { 0, 1 };

	for (size_t i = 0; i < numTextures; i++)
	{
		if (model->myTextures[indices[i]].size() == 0)
			continue;

		std::shared_ptr<Texture> texture = Engine::GetResourceManager().Get<Texture>(modelDirectory + model->myTextures[indices[i]]);

		for (size_t j = 0; j < GetMeshes().size(); j++)
		{
			GetMeshes()[j]->SetTexture(slotIndices[i], texture);
		}
	}

	delete model;

	Engine::GetLogger().LogResource("Finished loading model {0} in {1}ms.", myPath, loadWatch.GetElapsedTime().InMilliseconds());
}

AssimpMesh::AssimpMesh(CLoaderMesh * aMesh, const std::string & aModelDirectory)
	: Mesh(nullptr)
{
	const char * meshVertices = reinterpret_cast<const char*>(aMesh->myVerticies);

	std::vector<Vertex> vertices;
	vertices.resize(aMesh->myVertexCount);
	size_t readOffset = 0;
	for (size_t i = 0; i < vertices.size(); i++)
	{
		if ((aMesh->myShaderType & EModelBluePrint_Position) != 0)
		{
			vertices[i].position = *reinterpret_cast<const ::Vector4f*>(&meshVertices[readOffset]);
			readOffset += sizeof(::Vector4f);
		}
		else
		{
			vertices[i].position = ::Vector4f(0.f, 0.f, 0.f, 1.f);
		}

		if ((aMesh->myShaderType & EModelBluePrint_Normal) != 0)
		{
			vertices[i].normal = *reinterpret_cast<const ::Vector4f*>(&meshVertices[readOffset]);
			readOffset += sizeof(::Vector4f);
		}
		else
		{
			vertices[i].normal = ::Vector4f(0.f, 0.f, 0.f, 0.f);
		}

		if ((aMesh->myShaderType & EModelBluePrint_BinormTan) != 0)
		{
			vertices[i].tangent = *reinterpret_cast<const ::Vector4f*>(&meshVertices[readOffset]);
			readOffset += sizeof(::Vector4f);

			vertices[i].bitangent = *reinterpret_cast<const ::Vector4f*>(&meshVertices[readOffset]);
			readOffset += sizeof(::Vector4f);
		}
		else
		{
			vertices[i].tangent = ::Vector4f(0.f, 0.f, 0.f, 0.f);
			vertices[i].bitangent = ::Vector4f(0.f, 0.f, 0.f, 0.f);
		}

		if ((aMesh->myShaderType & EModelBluePrint_UV) != 0)
		{
			vertices[i].uv = *reinterpret_cast<const ::Vector2f*>(&meshVertices[readOffset]);
			readOffset += sizeof(::Vector2f);
		}
		else
		{
			vertices[i].uv = ::Vector2f(0.f, 0.f);
		}

		if ((aMesh->myShaderType & EModelBluePrint_Bones) != 0)
		{
			// vertices[i].position = *reinterpret_cast<const ::Vector4f*>(&meshVertices[i * aMesh->myVertexBufferSize]);
			readOffset += sizeof(::Vector4f);
			readOffset += sizeof(::Vector4f);
		}
		else
		{
			// vertices[i].position = ::Vector4f(0.f, 0.f, 0.f, 1.f);
		}
	}

	CreateMesh(vertices, aMesh->myIndexes);
}
