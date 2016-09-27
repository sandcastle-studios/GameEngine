#pragma once
#include "Game\Component\Controller\ControllerComponent.h"
class AIControllerComponent :
	public ControllerComponent
{
public:
	AIControllerComponent();
	virtual ~AIControllerComponent() override;

	virtual void Update(const Time & aDeltaTime) override;

};

