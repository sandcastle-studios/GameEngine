#pragma once

namespace ENGINE_NAMESPACE
{

	template <typename TIDType>
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

	template <typename TIDType>
	size_t UniqeIdentifier<TIDType>::nextTypeIndex = 0;

}