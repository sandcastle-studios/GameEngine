#pragma once
#include "Game\Component\Controller\ControllerComponent.h"

class AIControllerComponent : public ControllerComponent
{
public:
	AIControllerComponent();
	virtual ~AIControllerComponent() override;

	virtual void Update(const SB::Time & aDeltaTime) override;
};

