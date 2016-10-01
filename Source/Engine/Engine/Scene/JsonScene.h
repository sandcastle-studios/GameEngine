#pragma once
#include "Engine\Scene\Scene.h"

namespace ENGINE_NAMESPACE
{

	class JsonScene : public Scene
	{
	public:
		JsonScene(const char* aFilePath = "");
		~JsonScene();

		virtual void Update(const Time & aDeltaTime) override;
		virtual void Render() override;

	private:
		Sprite mySprite;
		std::shared_ptr<GameObject> myEnemy;
	};

}