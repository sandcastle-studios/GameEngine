#include "stdafx.h"
#include "Engine\Model\Mesh.h"
#include <d3dcommon.h>
#include <d3d11.h>
#include "Engine\Vertex\SimpleVertex.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Buffer\IndexBuffer.h"
#include "Engine\Effect\Effect.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Rendering\ModelRenderer.h"

GenericMesh::GenericMesh(const std::shared_ptr<Effect> & aEffect, const Surface & aSurface)
{
	myVertexCount = 0;
	myIndexCount = 0;
	myEffect = aEffect;
	mySurface = aSurface;
	myIdentifier = 0;
}

size_t GenericMesh::GetIdentifier() const
{
	return myIdentifier;
}

void GenericMesh::AssignIdentifier(size_t aIdentifier)
{
	if (myIdentifier != 0)
	{
		Engine::GetInstance().GetRenderer().GetModelRenderer().ReturnBatchIdentifier(myIdentifier);
	}
	myIdentifier = aIdentifier;
}

GenericMesh::~GenericMesh()
{
	if (myIdentifier != 0)
	{
		Engine::GetInstance().GetRenderer().GetModelRenderer().ReturnBatchIdentifier(myIdentifier);
		myIdentifier = 0;
	}
}

void GenericMesh::SetSurface(const Surface & aSurface)
{
	mySurface = aSurface;
}

void GenericMesh::SetEffect(const std::shared_ptr<Effect> & aEffect)
{
	myEffect = aEffect;
}

void GenericMesh::Render() const
{
	mySurface.BindToPS();

	myVertexBuffer->Bind(0);
	Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	myIndexBuffer->Bind();
	Engine::GetInstance().GetRenderer().GetContext()->DrawIndexed(myIndexCount, 0, 0);
}

void GenericMesh::RenderInstanced(int aInstanceCount) const
{
	mySurface.BindToPS();

	if (myEffect != nullptr)
	{
		myEffect->Bind();
	}

	myVertexBuffer->Bind(0);
	Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	myIndexBuffer->Bind();
	Engine::GetInstance().GetRenderer().GetContext()->DrawIndexedInstanced(myIndexCount, aInstanceCount, 0, 0, 0);
}

const BoundingBoxf & GenericMesh::GetBoundingBox()
{
	return myBoundingBox;
}

void GenericMesh::CreateMesh(const void * aVertexData, int aVertexCount, int aVertexSizeInBytes, const unsigned int * aIndexData, int aIndexCount)
{
	if (myVertexBuffer != nullptr)
	{
		Error("Mesh already created!");
		return;
	}

	myVertexBuffer = std::make_unique<GenericVertexBuffer>(aVertexData, aVertexCount * aVertexSizeInBytes, aVertexSizeInBytes);
	myIndexBuffer = std::make_unique<IndexBuffer>(aIndexData, aIndexCount);

	myVertexCount = aVertexCount;
	myIndexCount = aIndexCount;
}
