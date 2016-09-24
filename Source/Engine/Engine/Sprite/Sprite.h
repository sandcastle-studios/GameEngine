#pragma once

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Render();

	void SetTexture(const std::shared_ptr<const Texture> & aTexture);
	const std::shared_ptr<const Texture> & GetTexture() const;

	void SetPosition(const Vector2f & aPosition);
	const Vector2f & GetPosition() const;

	void SetColor(const Vector4f & aColor);
	const Vector4f & GetColor() const;

	void SetRotation(const float aRotation);
	float GetRotation() const;

	void SetOrigin(const Vector2f & aOrigin);
	const Vector2f & GetOrigin() const;

	void SetScale(const Vector2f & aScale);
	const Vector2f & GetScale() const;

	void SetEffect(const std::shared_ptr<const Effect> & aEffect);
	const std::shared_ptr<const Effect> & GetEffect() const;

	Matrix44f GenerateMatrix() const;

private:
	std::shared_ptr<const Texture> myTexture;
	std::shared_ptr<const Effect> myEffect;

	Vector4f myColor;
	Vector2f myPosition;
	Vector2f myOrigin;
	Vector2f myScale;
	float myRotation;
};

inline void Sprite::SetPosition(const Vector2f & aPosition)
{
	myPosition = aPosition;
}

inline const Vector2f & Sprite::GetPosition() const
{
	return myPosition;
}
