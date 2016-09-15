#include "stdafx.h"
#include "Mesh.h"
#include <d3dcommon.h>
#include <d3d11.h>
#include "SimpleVertex.h"
#include "VertexBuffer.h"
#include "DXRenderer.h"
#include "IndexBuffer.h"
#include "Effect.h"
#include "Texture.h"
#include "ModelRenderer.h"

GenericMesh::GenericMesh(const std::shared_ptr<Texture> & aTexture)
{
	myVertexCount = 0;
	myIndexCount = 0;
	myTexture = aTexture;
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

void GenericMesh::SetTexture(const std::shared_ptr<Texture> & aTexture)
{
	myTexture = aTexture;
}

void GenericMesh::Render() const
{
	if (myTexture != nullptr)
	{
		myTexture->BindToPS(0);
	}

	myVertexBuffer->Bind(0);
	Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	myIndexBuffer->Bind();
	Engine::GetInstance().GetRenderer().GetContext()->DrawIndexed(myIndexCount, 0, 0);
}

void GenericMesh::RenderInstanced(int aInstanceCount) const
{
	if (myTexture != nullptr)
	{
		myTexture->BindToPS(0);
	}

	if (myEffect != nullptr)
	{
		myEffect->Bind();
	}

	myVertexBuffer->Bind(0);
	Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	myIndexBuffer->Bind();
	Engine::GetInstance().GetRenderer().GetContext()->DrawIndexedInstanced(myIndexCount, aInstanceCount, 0, 0, 0);
}

std::shared_ptr<Texture> GenericMesh::GetTexture()
{
	return myTexture;
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
