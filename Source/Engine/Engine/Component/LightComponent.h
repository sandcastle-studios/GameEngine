#pragma once
#include "Engine\Component\BaseComponent.h"

namespace ENGINE_NAMESPACE
{
	namespace ENGINE_NAMESPACE
	{
		class LightComponent : public BaseComponent
		{
		public:
			LightComponent();
			~LightComponent();

			virtual void Construct() override;

			virtual void Destruct() override;

		};
	}
}
