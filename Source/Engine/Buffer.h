#pragma once

struct ID3D11Buffer;
enum D3D11_USAGE;

class Buffer
{
public:
	virtual ~Buffer();

	int GetSizeInBytes() const;

	bool IsImmutable() const;
	
protected:
	Buffer(UINT aBindFlags, D3D11_USAGE aUsage, UINT aCpuAccessFlags, UINT aMiscFlags, const void * aData, int aSizeInBytes);
	ID3D11Buffer * GetBuffer();
	ID3D11Buffer * GetBuffer() const;

	void UpdateData(const void * aData, int aSizeInBytes, bool aAllowResize = false);

private:
	UINT myBindFlags;
	D3D11_USAGE myUsageFlags;
	UINT myCpuAccessFlags;
	UINT myMiscFlags;
	int mySizeInBytes;

	ID3D11Buffer *myBuffer;

	void CreateBuffer(const void *aData, int aSizeInBytes);
};

inline ID3D11Buffer * Buffer::GetBuffer()
{
	return myBuffer;
}

inline ID3D11Buffer * Buffer::GetBuffer() const
{
	return myBuffer;
}
