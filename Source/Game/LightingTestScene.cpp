#include "stdafx.h"
#include "LightingTestScene.h"
#include <Engine\Model\AssimpModel.h>
#include <Engine\Model\ModelInstance.h>
#include <Engine\Effect\StandardEffect.h>
#include <Engine\Camera\Camera.h>
#include <Engine\Rendering\DXRenderer.h>
#include <Engine\Rendering\ModelRenderer.h>
#include <imgui.h>

LightingTestScene::LightingTestScene()
{
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/Modelviewer_Exempelmodell/K11_1415.fbx");
	//std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/unitsphere/sphere.fbx");
	myHead = std::make_shared<ModelInstance>(model);
	myObjects.push_back(myHead);
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_shared<AssimpModel>(myEffect, "models/tga_companioncube/companion.fbx")));

	myHead->SetMatrix(Matrix44f::CreateTranslation(0.f, 0.f, -5.f));

	auto bb = myHead->GetBoundingBox();

	GetCamera().SetPosition(bb.GetCenter() + Vector3f(0.f, 0.f, -bb.GetSize().z * 1.5f));
	// GetCamera().LookAt(Vector3f::Zero);

	Engine::GetRenderer().GetModelRenderer().SetDirectionalLight(0, Vector3f(0.f, 1.f, .5f), Vector4f(0.7f, 0.7f, 0.7f, 1.f));
}

LightingTestScene::~LightingTestScene()
{
}

void LightingTestScene::Update(const Time & aDeltaTime)
{
	ImGui::SetNextWindowPos({ 16, 16 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowSize({ 375, 400 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowCollapsed(true, ImGuiSetCond_Once);

	if (ImGui::Begin("Debug Window"))
	{
		static bool checked;
		ImGui::Checkbox("Checked", &checked);
	}

	ImGui::End();

	// myHead->SetMatrix(Matrix44f::CreateRotateAroundY(myTime.InSeconds()));

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

	Scene::Update(aDeltaTime);
}

void LightingTestScene::Render()
{
	Scene::Render();
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
