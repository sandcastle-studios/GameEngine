#pragma once

class ModelInstance;
class Camera;
class StandardEffect;

class Scene
{
public:
	Scene(const char * aSkyboxPath = nullptr);
	virtual ~Scene();

	virtual void Update(const Time & aDeltaTime);
	virtual void Render();

	Camera & GetCamera();

protected:
	std::vector<std::shared_ptr<ModelInstance>> myObjects;

	std::unique_ptr<ModelInstance> mySkybox;

	std::unique_ptr<Camera> myCamera;

	std::shared_ptr<StandardEffect> myEffect;

	Time myTime;
};

