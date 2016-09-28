#include "stdafx.h"
#include "LightingTestScene.h"
#include <AssimpModel.h>
#include <ModelInstance.h>
#include <StandardEffect.h>
#include <Camera.h>
#include "..\Engine\ConstantBuffer.h"
#include "..\Engine\LightLoader.h"
#include "..\Engine\PointLightInstance.h"
#include <CubeTexture.h>

LightingTestScene::LightingTestScene(const char* aSkyBoxPath) : Scene(aSkyBoxPath)
{
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/Sphere/testSpheres.fbx");
	myInstance = std::make_shared<ModelInstance>(model);
	//const char* lightID[4] = { "WhiteLight", "RedLight", "BlueLight", "GreenLight" };
	/*for (unsigned int i = 0; i < 4; i++)
	{
		std::shared_ptr<PointLightInstance> pointLightInstance = std::make_shared<PointLightInstance>(Vector3f(0, 0, -1.0), Engine::GetLightLoader().LoadPointLightModel(lightID[i]));
		myPointLightInstances.push_back(pointLightInstance);
	}*/

	myObjects.push_back(myInstance);

	GetCamera().SetPosition(Vector3f(0.f, 0.f, -8.f));
	GetCamera().LookAt(Vector3f::Zero);
	
	myCubeTexture = std::make_shared<CubeTexture>("models/cube_1024_preblurred_angle3_Skansen3.dds");

	myConstantBuffer = std::make_unique<ConstantBuffer<LightData>>();

}

LightingTestScene::~LightingTestScene()
{
}

void LightingTestScene::Render()
{
	LightData lightData;
	lightData.myDirectionalLight.myDirection = Vector4f(1.f, -1.f, 1.f, 1.f);
	lightData.myDirectionalLight.myColor = Vector4f(1.f, 1.f, 1.f, 1.f);
	lightData.mipMapCount = myCubeTexture->GetMipMapCount();
	/*for (unsigned int i = 0; i < 4; i++)
	{
		lightData.myPointLight[i].myColor = myPointLightInstances[i]->GetColor();
		lightData.myPointLight[i].myIntensity = myPointLightInstances[i]->GetIntensity();
		lightData.myPointLight[i].myRange = myPointLightInstances[i]->GetRange();
		lightData.myPointLight[i].myPosition = myPointLightInstances[i]->GetPosition();
	}*/
	myConstantBuffer->UpdateData(lightData);
	myConstantBuffer->BindToPS(1);

	myCubeTexture->BindToPS(6);

	Scene::Render();
}

void LightingTestScene::Update(const Time & aDeltaTime)
{

	GetCamera().SetPosition(Vector3f(sinf(myTime.InSeconds() * 0.5f), sinf(myTime.InSeconds() * 0.75f) * 0.2f, cosf(myTime.InSeconds() * 0.5f)) * 10.f);
	GetCamera().LookAt(Vector3f::Zero);

	//myInstance->SetMatrix(myInstance->GetMatrix() * Matrix44f::CreateRotateAroundY(1.f * aDeltaTime.InSeconds()));
	
	/*for (unsigned int index = 0; index < myPointLightInstances.size(); index++)
	{
		if (index % 2 == 0)
		{
			myPointLightInstances[index]->SetPosition(Vector4f(myPointLightInstances[index]->GetPosition(), 1.f) * Matrix44f::CreateRotateAroundY((index+1) * aDeltaTime.InSeconds()));
		}
		else
		{
			myPointLightInstances[index]->SetPosition(Vector4f(myPointLightInstances[index]->GetPosition(), 1.f) * Matrix44f::CreateRotateAroundX((index+1) * aDeltaTime.InSeconds()));
		}
	}*/

	Scene::Update(aDeltaTime);
}
