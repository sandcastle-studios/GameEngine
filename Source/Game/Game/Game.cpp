#include "stdafx.h"
#include "Game.h"
#include <Engine\Window\WindowsWindow.h>
#include <Engine\Window\WindowMessage.h>
#include <Engine\Rendering\DXRenderer.h>
#include <Engine\Camera\Camera.h>
#include <Engine\Time\Stopwatch.h>
#include <Engine\Scene\Scene.h>
#include "SlideShowScene.h"
#include "InstancedTestScene.h"
#include <Engine\FileWatcher\FileChangeWatcher.h>
//#include "LightingTestScene.h"
//#include <Engine\SplashScreen\SplashScreenScene.h>
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

	Engine::GetInstance().AttachDebugger(std::make_shared<Debugger>(myWindow->GetHandle()));

	Initialize();

	Stopwatch watch;

	while (myWindow->IsOpen())
	{
		Time deltaTime = watch.GetElapsedTime();
		watch.Restart();

		Engine::GetDebugger().NewFrame();

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
	Engine::GetResourceManager().Update();
	Engine::GetFileWatcher().PostChanges();

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

	Engine::GetDebugger().RenderFrame();

	Engine::GetInstance().GetRenderer().Present();
}

void Game::CreatePerspective()
{
	myScene->GetCamera().CreatePerspective(60.f, static_cast<float>(myWindow->GetSize().width), static_cast<float>(myWindow->GetSize().height), 100.f, 0.1f);
}
