#include "stdafx.h"
#include "AssimpModel.h"
#include <FBXLoader.h>
#include "Vertex.h"
#include "Texture.h"

AssimpModel::AssimpModel(const std::shared_ptr<Effect> & aEffect, const std::string & aFilePath)
	: Model(aEffect)
{
	CFBXLoader loader;
	CLoaderModel * model = loader.LoadModel(aFilePath.c_str());
	
	std::string modelDirectory;
	size_t lastSlash = aFilePath.find_last_of("\\/");
	if (lastSlash == std::string::npos)
	{
		modelDirectory = "";
	}
	else
	{
		modelDirectory = aFilePath.substr(0, lastSlash + 1);
	}

	for (size_t i = 0; i < model->myMeshes.size(); i++)
	{
		CLoaderMesh * mesh = model->myMeshes[i];

		AddMesh(std::make_shared<AssimpMesh>(mesh, modelDirectory));
	}


	for (size_t i = 0; i < model->myTextures.size(); i++)
	{
		// Model loader fills unused texture slots with an empty string, skip them
		if (model->myTextures[i].size() == 0)
			continue;

		std::shared_ptr<Texture> texture = Engine::GetResourceManager().Get<Texture>(modelDirectory + model->myTextures[i]);

		for (size_t j = 0; j < GetMeshes().size(); j++)
		{
			GetMeshes()[j]->SetTexture(texture);
		}

		// Only load the first texture for now
		break;
	}

	delete model;
}

AssimpModel::AssimpModel(const std::shared_ptr<Effect> & aEffect, const char * aFilePath)
	: AssimpModel(aEffect, std::string(aFilePath))
{
}

AssimpModel::~AssimpModel()
{
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
