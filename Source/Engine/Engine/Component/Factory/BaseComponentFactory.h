#pragma once

class Time;

class BaseComponentFactory
{
public:
	BaseComponentFactory();
	virtual ~BaseComponentFactory() = 0;

	virtual void Update(const Time & aDeltaTime);
	virtual void Render();
	virtual void ReturnMemory(unsigned short aIndex) = 0;
};

inline BaseComponentFactory::BaseComponentFactory()
{
}

inline BaseComponentFactory::~BaseComponentFactory()
{
}

inline void BaseComponentFactory::Update(const Time & aDeltaTime)
{
}

inline void BaseComponentFactory::Render()
{
}