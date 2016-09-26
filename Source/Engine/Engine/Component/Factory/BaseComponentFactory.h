#pragma once

class Time;

class BaseComponentFactory
{
public:
	BaseComponentFactory();
	virtual ~BaseComponentFactory();

	virtual void Update(const Time & aDeltaTime);
	virtual void Render();
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
