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

CockpitTestScene::CockpitTestScene()
{
	CreateFactories();
	
	myConstantBuffer = std::make_unique<ConstantBuffer<SplashScreenCBuffer>>();
	mySprite.SetTexture(Engine::GetResourceManager().Get<Texture>("textures/cockpitPlaceholder.dds"));
	mySprite.SetEffect(std::make_shared<SpriteEffect>());
}


CockpitTestScene::~CockpitTestScene()
{
}

void CockpitTestScene::Update(const Time & aDeltaTime)
{
	Scene::Update(aDeltaTime);
}

void CockpitTestScene::Render()
{
	myConstantBuffer->UpdateData(SplashScreenCBuffer{ Vector4f(myTime.InSeconds(), 0.f, 0.f, 0.f) });
	myConstantBuffer->BindToPS(2);
	Vector2f pos = Engine::GetRenderer().GetRenderTargetResolution() / 2.f;
	pos.x = std::floorf(pos.x);
	pos.y = std::floorf(pos.y);
	mySprite.SetPosition(Vector2f(0.f, 0.f));
	//mySprite.SetOrigin(mySprite.GetTexture()->GetSize() / 2.f);
	mySprite.Render();

	Scene::Render();
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