#include "stdafx.h"
#include "World.h"
#include <ModelInstance.h>
#include <DXRenderer.h>
#include <Camera.h>
#include <CubeModel.h>
#include <PlaneModel.h>
#include <Texture.h>
#include <Skybox.h>
#include "StandardEffect.h"
#include <RenderTexture.h>
#include <TextureDebugger.h>
#include <DepthBuffer.h>

World::World()
{
	myCamera = std::make_unique<Camera>();

	myEffect = std::make_shared<StandardEffect>();

	mySkybox = std::make_unique<ModelInstance>(std::make_shared<Skybox>(myEffect, std::make_shared<Texture>("skybox.dds")));
	myCube = std::make_shared<ModelInstance>(std::make_shared<CubeModel>(myEffect, std::make_shared<Texture>("cube.dds")));
	auto grass = std::make_shared<ModelInstance>(std::make_shared<PlaneModel>(myEffect, std::make_shared<Texture>("grass.dds"), 6, 6));
	
	myCube->SetMatrix(Matrix44f::CreateTranslation(0.f, 0.5f, 5.f));
	grass->SetMatrix(Matrix44f::CreateScale(15.f, 1.f, 15.f) * Matrix44f::CreateTranslation(0.f, 0.f, 5.f));

	myObjects.push_back(grass);
	myObjects.push_back(myCube);

	myRenderTexture = std::make_shared<RenderTexture>(500, 500);
}

World::~World()
{
}

void World::Update(const Time &aDeltaTime)
{
	myTime += aDeltaTime;

	myCamera->SetPosition(myCube->GetPosition() + Vector3f(
		std::cosf(myTime.InSeconds()) * 5.f,
		1.2f + std::sinf(myTime.InSeconds() / 2.f) * 1.f,
		std::sinf(myTime.InSeconds()) * 5.f
	));

	myCamera->LookAt(myCube->GetPosition());
}

void World::Render()
{
	myCamera->ApplySkyboxMatrixToVS();
	mySkybox->Render();
	Engine::GetInstance().GetRenderer().ClearDepthBuffer();

	myCamera->ApplyToVS();

	for (size_t i = 0; i < myObjects.size(); i++)
	{
		myObjects[i]->Render();
	}

	Engine::GetInstance().GetRenderer().GetTextureDebugger().QueueRender(myRenderTexture->GetTexture());
	Engine::GetInstance().GetRenderer().GetTextureDebugger().QueueRender(myCube->GetModel()->GetTexture());
	Engine::GetInstance().GetRenderer().GetTextureDebugger().QueueRender(Engine::GetInstance().GetRenderer().GetDepthBuffer()->GetTexture());
}

Camera & World::GetCamera()
{
	return *myCamera;
}
