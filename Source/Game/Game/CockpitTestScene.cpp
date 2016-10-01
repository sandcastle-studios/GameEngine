#include "stdafx.h"
#include "CockpitTestScene.h"
#include "Engine\Sprite\SpriteEffect.h"
#include <Engine\SplashScreen\SplashScreenScene.h>
#include <Engine\Model\AssimpModel.h>
#include "Engine\Model\ModelInstance.h"


#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine/Model/ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\Model\AssimpModel.h>
#include <Engine/Effect/StandardEffect.h>
#include <Engine\Camera/Camera.h>
#include "Engine\Resources\ResourceManager.h"
#include "Engine\SplashScreen\SplashScreenEffect.h"
#include <Engine\SplashScreen\SplashScreenScene.h>
#include <Engine\Camera\Controllers\FreeSpaceCameraController.h>

CockpitTestScene::CockpitTestScene()
{
	CreateFactories();
	
	mySprite.SetTexture(SB::Engine::GetResourceManager().Get<SB::Texture>("textures/cockpitPlaceholder.dds"));
	CreateAndAddModel("models/tga_companioncube/companion.fbx", SB::Vector3f(0.f, 0.f, 5.f));
	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(5.f, 2.f));
}


CockpitTestScene::~CockpitTestScene()
{
}

void CockpitTestScene::Update(const SB::Time & aDeltaTime)
{
	Scene::Update(aDeltaTime);
}

void CockpitTestScene::Render()
{
	Scene::Render();

	SB::Engine::GetRenderer().GetModelRenderer().RenderBuffer();

	SB::Vector2f pos = SB::Engine::GetRenderer().GetRenderTargetResolution() / 2.f;
	pos.x = std::floorf(pos.x);
	pos.y = std::floorf(pos.y);
	mySprite.SetOrigin(pos);
	mySprite.SetPosition(pos);
	mySprite.SetRotation(0.f);
	mySprite.SetScale(SB::Engine::GetRenderer().GetRenderTargetResolution() / SB::Vector2f(1920.f, 1080.f));
	mySprite.Render();
}

void CockpitTestScene::CreateFactories()
{
	//PreCreateComponentFactory<ModelComponent>();
	//PreCreateComponentFactory<LightComponent>();
	//
	//std::shared_ptr<GameObject> enemy = std::make_shared<GameObject>();
	//
	//SharedPtrComponent<ModelComponent> prettyModel(GetComponentFactory<ModelComponent>()->CreateComponent());
	//std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/unitsphere/sphere.fbx");
	//
	//myTestObject1 = std::make_shared<ModelInstance>(model);
	//
	//myTestObject1->SetMatrix(myTestObject1->GetMatrix() * Matrix44f::CreateScale(0.01f, 0.01f, 0.01f));
	//prettyModel->SetModel(myTestObject1);
	//
	//GetCamera().SetPosition(myTestObject1->GetBoundingBox().GetCenter() + Vector3f(0.f, 0.f, -myTestObject1->GetBoundingBox().GetSize().z * 1.5f));
	//
	//myObjects.Add(enemy);


}