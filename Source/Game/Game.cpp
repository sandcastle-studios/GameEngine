#include "stdafx.h"
#include "Game.h"
#include <WindowsWindow.h>
#include <WindowMessage.h>
#include <DXRenderer.h>
#include <Camera.h>
#include <Stopwatch.h>
#include <Scene.h>
#include "SlideShowScene.h"
#include "InstancedTestScene.h"
#include <FileChangeWatcher.h>
#include "LightingTestScene.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Start()
{
	Engine::CreateInstance();

	myWindow = std::make_unique<WindowsWindow>();
	myWindow->SetTitle("Game Engine");
	myWindow->SetSize(Size<int>(1280, 720));
	myWindow->Open();

	Engine::GetInstance().GetRenderer().Initialize(myWindow->GetHandle(), myWindow->GetSize().width, myWindow->GetSize().height, false);

	Initialize();

	Stopwatch watch;

	while (myWindow->IsOpen())
	{
		Time deltaTime = watch.GetElapsedTime();
		watch.Restart();

		ProcessMessages();

		Update(deltaTime);

		Render();
	}

	// Destroy our world releasing it's resources allowing the engine to shut down
	myScene = nullptr;

	Engine::DestroyInstance();
}

void Game::ProcessMessages()
{
	WindowMessage message;
	while (myWindow->PollMessage(message))
	{
		switch (message.type)
		{
		case WindowMessageType::eCloseButtonPressed:
			myWindow->Close();
			break;
		case WindowMessageType::eSizeChanged:
			Engine::GetInstance().GetRenderer().Resize(myWindow->GetSize().width, myWindow->GetSize().height);
			CreatePerspective();
			break;
		}
	}
}

void Game::Initialize()
{
	myScene = std::make_unique<LightingTestScene>();

	CreatePerspective();
}

void Game::Update(const Time &aDeltaTime)
{
	if (myScene != nullptr)
	{
		myScene->Update(aDeltaTime);
	}
}

void Game::Render()
{
	Engine::GetInstance().GetRenderer().ClearFrame();

	if (myScene != nullptr)
	{
		myScene->Render();
	}

	Engine::GetInstance().GetRenderer().Present();
}

void Game::CreatePerspective()
{
	myScene->GetCamera().CreatePerspective(60.f, static_cast<float>(myWindow->GetSize().width), static_cast<float>(myWindow->GetSize().height), 0.1f, 1000.f);
}
