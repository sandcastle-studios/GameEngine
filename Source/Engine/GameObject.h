#pragma once

class Scene;

class GameObject
{
public:
	GameObject();
	~GameObject();

	Scene & GetScene();
	const Scene & GetScene() const;

	template <typename TStateType>
	TStateType & GetState();

	template <typename TStateType>
	const TStateType & GetState() const;

private:
	Scene * myScene;
};

inline Scene & GameObject::GetScene()
{
	return *myScene;
}

inline const Scene & GameObject::GetScene() const
{
	return *myScene;
}
