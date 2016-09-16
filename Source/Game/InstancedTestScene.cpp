#include "stdafx.h"
#include "InstancedTestScene.h"
#include <AssimpModel.h>
#include <ModelInstance.h>
#include <StandardEffect.h>
#include <Camera.h>
#include <CubeModel.h>
#include <Texture.h>

InstancedTestScene::InstancedTestScene()
	: Scene("skybox.dds")
{
	// auto cube = std::make_shared<AssimpModel>(myEffect, "models/tga_companioncube/companion.fbx");
	auto cube = std::make_shared<CubeModel>(myEffect, std::make_shared<Texture>("models/tga_companioncube/companion_heart.dds"));

	float size = 10.f;
	float offset = 1.25f;
	for (float x = -size / 2.0f; x < size / 2.0f; x += 1.0f)
	{
		for (float y = -size / 2.0f; y < size / 2.0f; y += 1.0f)
		{
			for (float z = -size / 2.0f; z < size / 2.0f; z += 1.0f)
			{
				auto instance = std::make_shared<ModelInstance>(cube);
				instance->SetMatrix(Matrix44f::CreateTranslation(x * offset, y * offset, z * offset));
				myObjects.push_back(instance);
			}
		}
	}

	myCamera->SetPosition(Vector3f(-size * offset * 1.f, -size * offset * .5f, -size * offset * 1.5f));
	myCamera->LookAt(Vector3f::Zero);
}


InstancedTestScene::~InstancedTestScene()
{
}
