#include "stdafx.h"
#include "Engine\Model\Model.h"
#include "Engine\Effect\Effect.h"
#include "Engine\Model\Mesh.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Rendering\ModelRenderer.h"

Model::Model()
{
}

Model::Model(const std::shared_ptr<GenericMesh> & aMesh)
{
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
