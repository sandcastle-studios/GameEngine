#pragma once



template <typename TYPE>
class UniqeIdentifier
{
public:

	static size_t nextTypeIndex;

	template<typename T>
	static size_t GetID()
	{
		static size_t id = nextTypeIndex++;
		return id;
	}
};

template <typename TYPE>
size_t UniqeIdentifier::nextTypeIndex = 1;