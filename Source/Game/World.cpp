#include "stdafx.h"
#include "World.h"
#include <ModelInstance.h>
#include <DXRenderer.h>
#include <Camera.h>
#include <Texture.h>
#include <Skybox.h>
#include "StandardEffect.h"
#include <DepthBuffer.h>
#include <ModelRenderer.h>
#include <AssimpModel.h>
#include <RenderTexture.h>

World::World()
{
	myCamera = std::make_unique<Camera>();

	myEffect = std::make_shared<StandardEffect>();

	mySkybox = std::make_unique<ModelInstance>(std::make_shared<Skybox>(myEffect, std::make_shared<Texture>("skybox.dds")));

	myObjects.push_back(std::make_shared<ModelInstance>(std::make_unique<AssimpModel>(myEffect, "models/tga_companioncube/companion.fbx")));
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_unique<AssimpModel>(myEffect, "models/crystalAsteroid/crystalAsteroidHigh.fbx")));
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_unique<AssimpModel>(myEffect, "models/pillar/pillarShortObelisk.fbx")));
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_unique<AssimpModel>(myEffect, "models/Asteroid/AsteroidPillarHuge1.fbx")));
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_unique<AssimpModel>(myEffect, "models/Asteroid/AsteroidPillarLarge1.fbx")));
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_unique<AssimpModel>(myEffect, "models/Asteroid/AsteroidPillarLarge2.fbx")));
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_unique<AssimpModel>(myEffect, "models/Asteroid/AsteroidPillarLarge3.fbx")));
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_unique<AssimpModel>(myEffect, "models/Pistol/gunMesh.fbx")));
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_unique<AssimpModel>(myEffect, "models/m4a1/m4a1_s.fbx")));

	myCurrentModel = 0;
	myTimePerModel = Time::FromSeconds(5.0f);
	myModelTransitionTime = Time::FromSeconds(1.f);
}

World::~World()
{
}

void World::Update(const Time &aDeltaTime)
{
	myTime += aDeltaTime;
	myCurrentModelTime += aDeltaTime;
	
	if (myCurrentModelTime > myTimePerModel)
	{
		NextModel();
	}

	Vector3f nextModelPosition;
	for (size_t i = 0; i < myObjects.size(); i++)
	{
		myObjects[i]->SetMatrix(Matrix44f::CreateTranslation(-myObjects[i]->GetModel()->GetBoundingBox().GetCenter())
			* Matrix44f::CreateRotateAroundY(myTime.InSeconds())
			* Matrix44f::CreateTranslation(nextModelPosition));

		nextModelPosition.x += myObjects[i]->GetBoundingBox().GetMaximumRadius() * 1.05f;

		if (i + 1 < myObjects.size())
		{
			nextModelPosition.x += myObjects[i + 1]->GetBoundingBox().GetMaximumRadius() * 1.05f;
		}
	}

	BoundingBoxf currentObjectBoundingBox = myObjects[myCurrentModel]->GetBoundingBox();

	float progress = std::min(1.f, myCurrentModelTime.InSeconds() / myModelTransitionTime.InSeconds());
	progress = (1.f + std::sinf(-HalfPi + progress * Pi)) / 2.f;

	Vector3f cameraTo = currentObjectBoundingBox.GetCenter() + Vector3f(0.f, 0.f, -currentObjectBoundingBox.GetMaximumRadius() * 1.5f);
	myCamera->SetPosition(myCameraFrom + (cameraTo - myCameraFrom) * progress);
}

void World::Render()
{
	myCamera->ApplySkyboxMatrixToVS();
	mySkybox->Render();
	Engine::GetInstance().GetRenderer().GetModelRenderer().RenderBuffer();

	Engine::GetInstance().GetRenderer().GetBackBuffer()->GetDepthBuffer()->Clear();
	myCamera->ApplyToVS();

	for (size_t i = 0; i < myObjects.size(); i++)
	{
		myObjects[i]->Render();
	}

	Engine::GetInstance().GetRenderer().GetModelRenderer().RenderBuffer();
}

Camera & World::GetCamera()
{
	return *myCamera;
}

void World::NextModel()
{
	myCameraFrom = myCamera->GetPosition();
	myCurrentModel = (myCurrentModel + 1) % myObjects.size();
	myCurrentModelTime = 0.f;
}
