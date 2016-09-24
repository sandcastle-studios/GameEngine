#include "stdafx.h"
#include "Engine\Scene\SplashScreenScene.h"
#include "Engine\Buffer\ConstantBuffer.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Rendering\SpriteRenderer.h"
#include "Engine\Effect\InputLayout.h"
#include "Engine\Effect\Effect.h"
#include <dxgiformat.h>

SplashScreenScene::SplashScreenScene()
{
	myConstantBuffer = std::make_unique<ConstantBuffer<SplashScreenCBuffer>>();
	myTexture = std::make_unique<Texture>("textures/intrologo.dds");

	mySplashScreenEffect = std::make_shared<Effect>();
	mySplashScreenEffect->AttachVertexShader("shaders/splashscreen.fx", "VShader");
	mySplashScreenEffect->AttachPixelShader("shaders/splashscreen.fx", "PShader");

	InputLayout layout;
	layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("NORMAL", 0, DXGI_FORMAT_R32G32_FLOAT);

	layout.AddPerInstance("INSTANCE_MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
	layout.AddPerInstance("INSTANCE_MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);

	mySplashScreenEffect->Link(layout);
}

SplashScreenScene::~SplashScreenScene()
{
}

void SplashScreenScene::Update(const Time & aDeltaTime)
{
	Scene::Update(aDeltaTime);
}

void SplashScreenScene::Render()
{
	myConstantBuffer->UpdateData(SplashScreenCBuffer{ Vector4f(myTime.InSeconds(), 0.f, 0.f, 0.f) });
	myConstantBuffer->BindToPS(2	);
	Vector2f pos = Vector2f(1280.f, 720.f) / 2.f - myTexture->GetSize() / 2.f;
	pos.x = std::floorf(pos.x);
	pos.y = std::floorf(pos.y);
	/*Engine::GetRenderer().GetSpriteRenderer().RenderWholeTexture(myTexture, pos, myTexture->GetSize(), &mySplashScreenEffect);*/
	Scene::Render();
}
