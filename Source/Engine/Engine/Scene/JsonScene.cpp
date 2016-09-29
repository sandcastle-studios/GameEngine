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
	PushCameraController(std::make_shared<FreeSpaceCameraController>(500.f, 2.5f));
	SetCameraOrientation(Vector3f(0.f, 0.f, -15.f));
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
}


//PRIVATE FUNCTIONS:

