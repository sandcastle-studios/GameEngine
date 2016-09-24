#pragma once
#include "Engine\Buffer\Buffer.h"

class IndexBuffer : public Buffer
{
public:
	IndexBuffer(const unsigned int * aFirstIndex, unsigned int aIndexCount);
	IndexBuffer(const std::vector<unsigned int> & aIndices);
	void Bind();
	~IndexBuffer();

	int GetCount() const;
};

