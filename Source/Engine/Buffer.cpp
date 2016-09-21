#include "stdafx.h"
#include "Buffer.h"
#include <d3d11.h>
#include <D3Dcommon.h>
#include "DXRenderer.h"

Buffer::Buffer(UINT aBindFlags, D3D11_USAGE aUsage, UINT aCpuAccessFlags, UINT aMiscFlags, const void * aData, int aSizeInBytes)
{
	myBindFlags = aBindFlags;
	myUsageFlags = aUsage;
	myCpuAccessFlags = aCpuAccessFlags;
	myMiscFlags = aMiscFlags;
	mySizeInBytes = aSizeInBytes;

	myBuffer = nullptr;

	CreateBuffer(aData, aSizeInBytes);
}

Buffer::~Buffer()
{
	SAFE_RELEASE(myBuffer);
}

int Buffer::GetSizeInBytes() const
{
	return mySizeInBytes;
}

bool Buffer::IsImmutable() const
{
	return (myUsageFlags & D3D11_USAGE_IMMUTABLE) != 0;
}

void Buffer::UpdateData(const void * aData, int aSizeInBytes, bool aAllowResize)
{
	if (IsImmutable())
	{
		Error("Tried to update an immutable buffer");
		return;
	}

	if (aSizeInBytes > mySizeInBytes)
	{
		if (aAllowResize)
		{
			SAFE_RELEASE(myBuffer);
			CreateBuffer(aData, aSizeInBytes);
			return;
		}
		else
		{
			Error("Data sent to buffer in UpdateData did not fit and aAllowResize is false");
			return;
		}
	}

	D3D11_MAPPED_SUBRESOURCE mappedObjectResource;
	
	CheckDXError(
		Engine::GetInstance().GetRenderer().GetContext()->Map(myBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedObjectResource);
	);

	memcpy(mappedObjectResource.pData, aData, aSizeInBytes);

	Engine::GetInstance().GetRenderer().GetContext()->Unmap(myBuffer, 0);
}

void Buffer::CreateBuffer(const void *aData, int aSizeInBytes)
{
	// Fill in a buffer description.
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = myUsageFlags;
	bufferDesc.ByteWidth = static_cast<UINT>(aSizeInBytes);
	bufferDesc.BindFlags = myBindFlags;
	bufferDesc.CPUAccessFlags = myCpuAccessFlags;
	bufferDesc.MiscFlags = myMiscFlags;

	// Fill in the data.
	D3D11_SUBRESOURCE_DATA initialData;
	initialData.pSysMem = aData;
	initialData.SysMemPitch = 0;
	initialData.SysMemSlicePitch = 0;

	// CreateInputLayout the vertex buffer.
	CheckDXError(
		Engine::GetRenderer().GetDevice()->CreateBuffer(&bufferDesc, aData == nullptr ? nullptr : &initialData, &myBuffer)
	);
}
