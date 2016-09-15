#include "stdafx.h"
#include "Model.h"
#include "Effect.h"
#include "Mesh.h"
#include "DXRenderer.h"
#include "ModelRenderer.h"

Model::Model(const std::shared_ptr<Effect> & aEffect)
{
	myEffect = aEffect;
}

Model::Model(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<GenericMesh> & aMesh)
{
	myEffect = aEffect;
	AddMesh(aMesh);
}

Model::~Model()
{
}

void Model::Render(const Matrix44f & aMatrix) const
{
	ModelRenderer & modelRenderer = Engine::GetInstance().GetRenderer().GetModelRenderer();
	for (size_t i = 0; i < myMeshes.size(); i++)
	{
		modelRenderer.Render(myMeshes[i], aMatrix);
	}
}

void Model::InstantRender(const Matrix44f & aWorldMatrix) const
{
	ModelRenderer & modelRenderer = Engine::GetInstance().GetRenderer().GetModelRenderer();
	modelRenderer.PrepareInstantRender(aWorldMatrix);

	for (size_t i = 0; i < myMeshes.size(); i++)
	{
		modelRenderer.InstantRender(myMeshes[i]);
	}
}

void Model::AddMesh(const std::shared_ptr<GenericMesh> & aMesh)
{
	aMesh->myEffect = myEffect;
	myMeshes.push_back(aMesh);

	BoundingBoxf bb = aMesh->GetBoundingBox();
	if (myMeshes.size() == 0)
	{
		myBoundingBox.SetToPosition(bb.GetCenter());
	}
	myBoundingBox.ExpandToContain(bb);
}

const std::vector<std::shared_ptr<GenericMesh>> & Model::GetMeshes() const
{
	return myMeshes;
}

const BoundingBoxf & Model::GetBoundingBox() const
{
	return myBoundingBox;
}

void Model::SetEffect(const std::shared_ptr<Effect> & aEffect)
{
	myEffect = aEffect;

	for (size_t i = 0; i < myMeshes.size(); i++)
	{
		myMeshes[i]->myEffect = aEffect;
	}
}
