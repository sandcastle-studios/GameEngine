#pragma once
#include <Engine\Component\BaseComponent.h>

class Model;
class Scene;

class PlayerShootComponent : public BaseComponent
{
public:
	virtual void Construct() override;
	virtual void Destruct() override;

	ReceiveResult Receive(const KeyDownMessage<KeyboardKey::eReturn> & aMessage);
	ReceiveResult Receive(const KeyUpMessage<KeyboardKey::eReturn> & aMessage);


	virtual void Update(const Time & aDeltaTime) override;

private:
	std::shared_ptr<Model> myModel;
	std::shared_ptr<Subscription<KeyDownMessage<KeyboardKey::eReturn>>> myKeySubscription;
	std::shared_ptr<Subscription<KeyUpMessage<KeyboardKey::eReturn>>> myKeyUpSubscription;
	int myShotCounter;
	bool myShooting;
	Time myShootTimer;
};

