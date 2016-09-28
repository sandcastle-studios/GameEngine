#pragma once
#include "Engine\Component\BaseComponent.h"
class LightComponent :
	public BaseComponent
{
public:
	LightComponent();
	~LightComponent();

	virtual void Construct() override;

	virtual void Destruct() override;

};

