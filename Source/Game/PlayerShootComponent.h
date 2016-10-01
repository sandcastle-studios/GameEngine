#pragma once
#include <Engine\Component\BaseComponent.h>

namespace SB
{
	class Model;
	class Scene;
}

class PlayerShootComponent : public SB::BaseComponent
{
public:
	virtual void Construct() override;
	virtual void Destruct() override;

	SB::ReceiveResult Receive(const SB::KeyDownMessage<SB::KeyboardKey::eReturn> & aMessage);
	SB::ReceiveResult Receive(const SB::KeyUpMessage<SB::KeyboardKey::eReturn> & aMessage);


	virtual void Update(const SB::Time & aDeltaTime) override;

private:
	std::shared_ptr<SB::Model> myModel;
	std::shared_ptr<SB::Subscription<SB::KeyDownMessage<SB::KeyboardKey::eReturn>>> myKeySubscription;
	std::shared_ptr<SB::Subscription<SB::KeyUpMessage<SB::KeyboardKey::eReturn>>> myKeyUpSubscription;
	int myShotCounter;
	bool myShooting;
	SB::Time myShootTimer;
};

