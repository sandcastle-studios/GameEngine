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

	void SetScene(Scene & aScene);

private:
	Scene * myScene;
	std::shared_ptr<Model> myModel;
	std::shared_ptr<Subscription<KeyDownMessage<KeyboardKey::eReturn>>> myKeySubscription;
	int myShotCounter;
};

