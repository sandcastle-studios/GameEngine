#pragma once


class ControllerComponent : public BaseComponent
{
public:
	ControllerComponent();
	virtual ~ControllerComponent() = 0;

	

	virtual void Update(const Time & aDeltaTime) override;

};

