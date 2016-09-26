#pragma once
#include <Utilities/Container/GrowingArray.h>
#include "Engine/Component/Factory/BaseComponentFactory.h"

template <typename TComponentType>
class ComponentFactory : public BaseComponentFactory
{
public:
	ComponentFactory() {};
	~ComponentFactory() {};

	std::shared_ptr<TComponentType> CreateComponent()
	{
		myComponents.Add(std::make_shared<TComponentType>());
		return myComponents.GetLast();
	}

	virtual void Update(const Time & aDeltaTime) override;

	virtual void Render() override;

private:
	GrowingArray<std::shared_ptr<TComponentType>> myComponents;
};

template <typename TComponentType>
inline void ComponentFactory<TComponentType>::Update(const Time & aDeltaTime)
{
	for (size_t iComponent = 0; iComponent < myComponents.Size(); ++iComponent)
	{
		myComponents[iComponent]->Update(aDeltaTime);
	}
}

template <typename TComponentType>
inline void ComponentFactory<TComponentType>::Render()
{
	for (size_t iComponent = 0; iComponent < myComponents.Size(); ++iComponent)
	{
		myComponents[iComponent]->Render();
	}
}