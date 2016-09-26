#include "stdafx.h"
#include "LightingTestScene.h"
#include <Engine\Model\AssimpModel.h>
#include <Engine\Model\ModelInstance.h>
#include <Engine\Effect\StandardEffect.h>
#include <Engine\Camera\Camera.h>
#include <Engine\Rendering\DXRenderer.h>
#include <Engine\Rendering\ModelRenderer.h>
#include <imgui.h>
#include <Engine\Texture\TextureDebugger.h>
#include <Engine\Texture\MultiRenderTexture.h>
#include <Engine\Texture\RenderTexture.h>
#include "..\Engine\Engine\RenderingConfiguration\BlendState.h"

float RandomFloat(const float aMin = 0.f, const float aMax = 1.0f)
{
	return aMin + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (aMax - aMin);
}

LightingTestScene::LightingTestScene()
{
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(nullptr, "models/Modelviewer_Exempelmodell/K11_1415.fbx");
	
	myHead = std::make_shared<ModelInstance>(model);
	myObjects.push_back(myHead);
	auto boundingBox = myHead->GetBoundingBox();
	GetCamera().SetPosition(boundingBox.GetCenter() + Vector3f(0.f, 0.f, -boundingBox.GetSize().z * 1.5f));
	
	myLightCount = 4;
	myMinSpeed = 0.3f;
	myMaxSpeed = 0.7f;
	myDirectionalLightIntensity = 0.1f;
	RandomizeLights();

	myTexture = Engine::GetResourceManager().Get<Texture>("grass.dds");
}

void LightingTestScene::RandomizeLights()
{
	BoundingBoxf boundingBox = myHead->GetBoundingBox();

	/*for (int i = 0; i < 8; i++)
	{
		if (i < myLightCount)
		{
			Vector3f position(boundingBox.GetCenter());
			const float pitch = RandomFloat() * TwoPi;
			const float yaw = RandomFloat() * TwoPi;
			position += Vector4f(boundingBox.GetMaximumRadius() * .25f, 0.f, 0.f, 1.f) * (Matrix44f::CreateRotateAroundY(yaw) * Matrix44f::CreateRotateAroundZ(pitch));
			Vector3f color(RandomFloat(), RandomFloat(), RandomFloat());
			color = Vector3f(1.f, 1.f, 1.f);

			myLightRotationAxises[i] = Vector2f(myMinSpeed + RandomFloat() * (myMaxSpeed - myMinSpeed), myMinSpeed + RandomFloat() * (myMaxSpeed - myMinSpeed)) * 3.f;

			Engine::GetRenderer().GetModelRenderer().SetPointLight(i, position, color, 0.2f + RandomFloat() * 0.8f, 1.0f);
		}
		else
		{
			Engine::GetRenderer().GetModelRenderer().SetPointLight(i, Vector3f::Zero, Vector3f::Zero, 1.0f, 0.0f);
		}
	}*/

	Engine::GetRenderer().GetModelRenderer().SetPointLight(0, boundingBox.GetCenter() + Vector3f(0.f, 0.f, -boundingBox.GetSize().z * 0.75f), Vector3f::One, 1.0f, 1.0f);
}

LightingTestScene::~LightingTestScene()
{
}

void LightingTestScene::Update(const Time & aDeltaTime)
{
	ImGui::SetNextWindowCollapsed(false, ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(16.f, 16.f), ImGuiSetCond_Once);
	//ImGui::SetNextWindowSize(ImVec2(300.f, 110.f), ImGuiSetCond_Once);
	
	if (ImGui::Begin("Lights", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::SliderFloat("Direction light intensity", &myDirectionalLightIntensity, 0.f, 1.f);
		Engine::GetRenderer().GetModelRenderer().SetDirectionalLight(0, Vector3f(0.f, 1.f, .5f), Vector4f(myDirectionalLightIntensity, myDirectionalLightIntensity, myDirectionalLightIntensity, 1.f));
		

		ImGui::SliderInt("Light count", &myLightCount, 0, 8);

		ImGui::DragFloatRange2("Light Speed", &myMinSpeed, &myMaxSpeed, 0.05f, -10.f, 10.f);

		if (ImGui::Button("Recreate lights"))
		{
			RandomizeLights();
		}
	}

	ImGui::End();

	for (auto && texture : Engine::GetRenderer().GetModelRenderer().GetDeferredTexture()->GetRenderTextures())
	{
		Engine::GetRenderer().GetTextureDebugger().QueueRender(texture->GetTexture());
	}
	Engine::GetRenderer().GetTextureDebugger().QueueRender(Engine::GetRenderer().GetModelRenderer().GetLambertTexture()->GetTexture());
	Engine::GetRenderer().GetTextureDebugger().QueueRender(Engine::GetRenderer().GetModelRenderer().GetDeferredTexture()->GetDepthBuffer()->GetTexture());

	/*{
		const LightConstantBufferData & lightData = Engine::GetRenderer().GetModelRenderer().GetLightData();

		for (int i = 0; i < 8; i++)
		{
			Vector3f pos = lightData.pointLight[i].position;
			pos = Vector4f(pos - myHead->GetBoundingBox().GetCenter(), 1.0f)
				* Matrix44f::CreateRotateAroundY(myLightRotationAxises[i].y * aDeltaTime.InSeconds())
				* Matrix44f::CreateRotateAroundX(myLightRotationAxises[i].x * aDeltaTime.InSeconds())
				+ Vector4f(myHead->GetBoundingBox().GetCenter(), 1.0f);

			Engine::GetRenderer().GetModelRenderer().SetPointLight(i, pos, lightData.pointLight[i].color, lightData.pointLight[i].radius, lightData.pointLight[i].intensity);
		}
	}*/

	CameraMovement(aDeltaTime);

	Scene::Update(aDeltaTime);
}

void LightingTestScene::Render()
{
	Engine::GetRenderer().GetModelRenderer().GetDeferredTexture()->Bind();
	Engine::GetRenderer().GetModelRenderer().GetDeferredTexture()->Clear();
	Engine::GetRenderer().GetModelRenderer().GetLambertTexture()->Clear(Vector4f(0.f, 0.f, 0.f, 0.f));

	Scene::Render();

	Engine::GetRenderer().GetModelRenderer().RenderLights();

	myEffect->Bind();
	Engine::GetRenderer().GetBackBuffer()->Bind(0, true);
}

void LightingTestScene::CameraMovement(const Time &aDeltaTime)
{
	if (myRollLeft)
	{
		myCamera->GetRototation().RotateZ(-aDeltaTime.InSeconds());
	}
	if (myRollRight)
	{
		myCamera->GetRototation().RotateZ(aDeltaTime.InSeconds());
	}

	const float speed = 1.f;

	if (myMoveLeft)
	{
		myCamera->AddPosition(myCamera->GetRototation().GetLeft() * speed * aDeltaTime.InSeconds());
	}
	if (myMoveRight)
	{
		myCamera->AddPosition(myCamera->GetRototation().GetRight() * speed * aDeltaTime.InSeconds());
	}

	if (myMoveForward)
	{
		myCamera->AddPosition(myCamera->GetRototation().GetForward() * speed * aDeltaTime.InSeconds());
	}
	if (myMoveBackward)
	{
		myCamera->AddPosition(myCamera->GetRototation().GetBackward() * speed * aDeltaTime.InSeconds());
	}

	if (myMoveUp)
	{
		myCamera->AddPosition(myCamera->GetRototation().GetUpward() * speed * aDeltaTime.InSeconds());
	}
	if (myMoveDown)
	{
		myCamera->AddPosition(myCamera->GetRototation().GetDownward() * speed * aDeltaTime.InSeconds());
	}

	const float rotateSpeed = 1.f;

	if (myPitchForward)
	{
		myCamera->GetRototation().RotateX(rotateSpeed * aDeltaTime.InSeconds());
	}
	if (myPitchBackward)
	{
		myCamera->GetRototation().RotateX(-rotateSpeed * aDeltaTime.InSeconds());
	}
	if (myRotateLeft)
	{
		myCamera->GetRototation().RotateY(rotateSpeed * aDeltaTime.InSeconds());
	}
	if (myRotateRight)
	{
		myCamera->GetRototation().RotateY(-rotateSpeed * aDeltaTime.InSeconds());
	}
}
ReceiveResult LightingTestScene::Receive(const AnyKeyDownMessage& aMessage)
{
	switch (aMessage.key)
	{
	case KeyboardKey::eQ:
		myRollLeft = true;
		break;
	case KeyboardKey::eE:
		myRollRight = true;
		break;

	case KeyboardKey::eA:
		myMoveLeft = true;
		break;
	case KeyboardKey::eD:
		myMoveRight = true;
		break;
	case KeyboardKey::eW:
		myMoveForward = true;
		break;
	case KeyboardKey::eS:
		myMoveBackward = true;
		break;

	case KeyboardKey::eLeft:
		myRotateLeft = true;
		break;
	case KeyboardKey::eRight:
		myRotateRight = true;
		break;
	case KeyboardKey::eUp:
		myPitchForward = true;
		break;
	case KeyboardKey::eDown:
		myPitchBackward = true;
		break;

	case KeyboardKey::eControl:
		myMoveDown = true;
		break;
	case KeyboardKey::eSpace:
		myMoveUp = true;
		break;

	case KeyboardKey::eAlt:
		Engine::GetLogger().LogInfo("eAlt pressed");
		break;
	}
	return ReceiveResult::eContinue;
}

ReceiveResult LightingTestScene::Receive(const AnyKeyUpMessage& aMessage)
{
	switch (aMessage.key)
	{
	case KeyboardKey::eQ:
		myRollLeft = false;
		break;
	case KeyboardKey::eE:
		myRollRight = false;
		break;

	case KeyboardKey::eA:
		myMoveLeft = false;
		break;
	case KeyboardKey::eD:
		myMoveRight = false;
		break;
	case KeyboardKey::eW:
		myMoveForward = false;
		break;
	case KeyboardKey::eS:
		myMoveBackward = false;
		break;

	case KeyboardKey::eLeft:
		myRotateLeft = false;
		break;
	case KeyboardKey::eRight:
		myRotateRight = false;
		break;
	case KeyboardKey::eUp:
		myPitchForward = false;
		break;
	case KeyboardKey::eDown:
		myPitchBackward = false;
		break;

	case KeyboardKey::eControl:
		myMoveDown = false;
		break;
	case KeyboardKey::eSpace:
		myMoveUp = false;
		break;
	}
	return ReceiveResult::eContinue;
}
