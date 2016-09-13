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
#include "..\Engine\ModelRenderer.h"
#include "..\Engine\ModelBatch.h"
#include <SpriteRenderer.h>

World::World()
{
	myCamera = std::make_unique<Camera>();

	myEffect = std::make_shared<StandardEffect>();

	mySkybox = std::make_unique<ModelInstance>(std::make_shared<Skybox>(myEffect, std::make_shared<Texture>("skybox.dds")));

	/*auto grass = std::make_shared<ModelInstance>(std::make_shared<PlaneModel>(myEffect, std::make_shared<Texture>("grass.dds"), 6, 6));
	grass->SetMatrix(Matrix44f::CreateScale(15.f, 1.f, 15.f) * Matrix44f::CreateTranslation(0.f, 0.f, 5.f));
	myObjects.push_back(grass);*/

	const float objectWidth = 25.f;

	auto cubeModel = std::make_shared<CubeModel>(myEffect, std::make_shared<Texture>("cube.dds"));

	//std::vector<Matrix44f> cubes;

	for (float x = -objectWidth / 2.f; x < objectWidth / 2.f; x++)
	{
		for (float y = -objectWidth / 2.f; y < objectWidth / 2.f; y++)
		{
			for (float z = -objectWidth / 2.f; z < objectWidth / 2.f; z++)
			{
				auto cube = std::make_shared<ModelInstance>(cubeModel);
				cube->SetMatrix(Matrix44f::CreateTranslation(x * 2.5f, y * 2.5f, z * 2.5f));
				myObjects.push_back(cube);
			}
		}
	}

	//myModelBatch = std::make_unique<ModelBatch>(cubeModel, cubes);
	
	myRenderTexture = std::make_shared<RenderTexture>(static_cast<int>(1280.f * 2.f), static_cast<int>(720.f * 2.f), true);
}

World::~World()
{
}

void World::Update(const Time &aDeltaTime)
{
	myTime += aDeltaTime;

	myCamera->SetPosition(Vector4f(-25.f * 2.5f, 12.5f * 2.5f, -30.f * 2.5f, 1.f) * Matrix44f::CreateRotateAroundY(myTime.InSeconds()));
	myCamera->LookAt(Vector3f());

	/*myCamera->SetPosition(myCube->GetPosition() + Vector3f(
		std::cosf(myTime.InSeconds()) * 5.f,
		1.2f + std::sinf(myTime.InSeconds() / 2.f) * 1.f,
		std::sinf(myTime.InSeconds()) * 5.f
	));

	myCamera->LookAt(myCube->GetPosition());*/
}

void World::Render()
{
	myRenderTexture->Bind(0);
	myRenderTexture->Clear(Vector4f(0.f, 0.f, 0.f, 0.f));

	myCamera->ApplySkyboxMatrixToVS();
	mySkybox->Render();
	Engine::GetInstance().GetRenderer().GetModelRenderer().RenderBuffer();
	myRenderTexture->GetDepthBuffer()->Clear();
	myCamera->ApplyToVS();

	for (size_t i = 0; i < myObjects.size(); i++)
	{
		myObjects[i]->Render();
	}

	Engine::GetInstance().GetRenderer().GetModelRenderer().RenderBuffer();
	
	Engine::GetInstance().GetRenderer().GetBackBuffer()->Bind(0);

	Engine::GetInstance().GetRenderer().GetSpriteRenderer().RenderWholeTexture(myRenderTexture->GetTexture(), Vector2f(), Vector2f(1280.f, 720.f));

	//myModelBatch->Render();

	// Engine::GetInstance().GetRenderer().GetTextureDebugger().QueueRender(myRenderTexture->GetTexture());
	// Engine::GetInstance().GetRenderer().GetTextureDebugger().QueueRender(myCube->GetModel()->GetTexture());
	// Engine::GetInstance().GetRenderer().GetTextureDebugger().QueueRender(Engine::GetInstance().GetRenderer().GetDepthBuffer()->GetTexture());
}

Camera & World::GetCamera()
{
	return *myCamera;
}
