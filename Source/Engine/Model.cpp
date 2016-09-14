#include "stdafx.h"
#include "Model.h"
#include "Effect.h"
#include "Mesh.h"

Model::Model(std::shared_ptr<Effect> aEffect)
{
	myEffect = aEffect;
}

Model::Model(std::shared_ptr<Effect> aEffect, std::shared_ptr<GenericMesh> aMesh)
{
	myEffect = aEffect;
	AddMesh(aMesh);
}

Model::~Model()
{
}

void Model::Render() const
{
	if (myEffect != nullptr)
	{
		myEffect->Bind();
	}

	for (size_t i = 0; i < myMeshes.size(); i++)
	{
		myMeshes[i]->Render();
	}
}

void Model::AddMesh(std::shared_ptr<GenericMesh> aMesh)
{
	myMeshes.push_back(aMesh);

	myBoundingBox.ExpandToContain(aMesh->GetBoundingBox());
}

const std::vector<std::shared_ptr<GenericMesh>> & Model::GetMeshes() const
{
	return myMeshes;
}

const BoundingBoxf & Model::GetBoundingBox() const
{
	return myBoundingBox;
}
