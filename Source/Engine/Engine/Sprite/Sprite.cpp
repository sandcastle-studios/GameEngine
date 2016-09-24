#include "stdafx.h"
#include "Sprite.h"
#include "Engine/Rendering/SpriteRenderer.h"

Sprite::Sprite()
{
	myColor = Vector4f(1.f, 1.f, 1.f, 1.f);
	myScale = Vector2f(1.f, 1.f);
}

Sprite::~Sprite()
{
}

void Sprite::Render()
{
	Engine::GetRenderer().GetSpriteRenderer().Render(*this);
}

void Sprite::SetTexture(const std::shared_ptr<const Texture> & aTexture)
{
	myTexture = aTexture;
}

const std::shared_ptr<const Texture> & Sprite::GetTexture() const
{
	return myTexture;
}

void Sprite::SetColor(const Vector4f & aColor)
{
	myColor = aColor;
}

const Vector4f & Sprite::GetColor() const
{
	return myColor;
}

void Sprite::SetRotation(const float aRotation)
{
	myRotation = aRotation;
}

float Sprite::GetRotation() const
{
	return myRotation;
}

void Sprite::SetOrigin(const Vector2f & aOrigin)
{
	myOrigin = aOrigin;
}

const Vector2f & Sprite::GetOrigin() const
{
	return myOrigin;
}

void Sprite::SetScale(const Vector2f & aScale)
{
	myScale = aScale;
}

const Vector2f & Sprite::GetScale() const
{
	return myScale;
}

Matrix44f Sprite::GenerateMatrix() const
{
	Vector2f renderSize = Engine::GetRenderer().GetRenderTargetResolution();
	Vector2f textureSize = myTexture->GetSize();

	return Matrix44f::CreateScale(textureSize.x, textureSize.y, 1.f)
		* Matrix44f::CreateTranslation(myPosition.x - myOrigin.x - renderSize.x / 2.f, myPosition.y - myOrigin.y - renderSize.y / 2.f, 0.f)
		* Matrix44f::CreateScale(myScale.x, myScale.y, 1.f)
		* Matrix44f::CreateRotateAroundZ(myRotation)
		* Matrix44f::CreateScale(2.0f / renderSize.x, -2.0f / renderSize.y, 1.f);
}

void Sprite::SetEffect(const std::shared_ptr<const Effect> & aEffect)
{
	myEffect = aEffect;
}

const std::shared_ptr<const Effect> & Sprite::GetEffect() const
{
	return myEffect;
}
