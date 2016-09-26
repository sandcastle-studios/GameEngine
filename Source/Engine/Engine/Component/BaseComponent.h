#pragma once


class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent();

	virtual void Update(const Time & aDeltaTime);

	virtual void Render() const;

};

