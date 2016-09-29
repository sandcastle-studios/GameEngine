#include "stdafx.h"
#include "JsonScene.h"
#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine\Model\ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\Model\AssimpModel.h>
#include <Engine\Effect\StandardEffect.h>
#include <Engine\Camera\Camera.h>
#include <Engine\DataParser\DataParser.h>
#include <Engine\Camera\Controllers\FreeSpaceCameraController.h>


JsonScene::JsonScene(const char* aFilePath) : Scene(aFilePath, "grass.dds")
{
	PushCameraController(std::make_shared<FreeSpaceCameraController>(10.f, 2.5f));
	SetCameraOrientation(Vector3f(0.f, 0.f, -15.f));
	mySprite.SetTexture(Engine::GetResourceManager().Get<Texture>("textures/cockpitPlaceholder.dds"));
}


JsonScene::~JsonScene()
{
}

void JsonScene::Update(const Time & aDeltaTime)
{

	Scene::Update(aDeltaTime);
}

void JsonScene::Render()
{
	Scene::Render();

	Engine::GetRenderer().GetModelRenderer().RenderBuffer();

	Vector2f pos = Engine::GetRenderer().GetRenderTargetResolution() / 2.f;
	pos.x = std::floorf(pos.x);
	pos.y = std::floorf(pos.y);
	mySprite.SetOrigin(pos);
	mySprite.SetPosition(pos);
	mySprite.SetRotation(0.f);
	mySprite.SetScale(Engine::GetRenderer().GetRenderTargetResolution() / Vector2f(1920.f, 1080.f));
	mySprite.Render();
}


//PRIVATE FUNCTIONS:

