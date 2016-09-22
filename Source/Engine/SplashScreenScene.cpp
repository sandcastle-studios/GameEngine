#include "stdafx.h"
#include "SplashScreenScene.h"
#include "Buffer\ConstantBuffer.h"
#include "Texture\Texture.h"
#include "Rendering\DXRenderer.h"
#include "Rendering\SpriteRenderer.h"
#include "Effect\InputLayout.h"
#include "Effect\Effect.h"
#include <dxgiformat.h>

SplashScreenScene::SplashScreenScene()
{
	myConstantBuffer = std::make_unique<ConstantBuffer<SplashScreenCBuffer>>();
	myTexture = std::make_unique<Texture>("textures/intrologo.dds");

	mySplashScreenEffect = std::make_shared<Effect>();
	mySplashScreenEffect->AttachVertexShader("splashscreen.fx", "VShader");
	mySplashScreenEffect->AttachPixelShader("splashscreen.fx", "PShader");

	InputLayout layout;
	layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("BITANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT);

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
	Engine::GetRenderer().GetSpriteRenderer().RenderWholeTexture(myTexture, pos, myTexture->GetSize(), &mySplashScreenEffect);
	Scene::Render();
}
