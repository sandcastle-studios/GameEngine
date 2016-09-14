#pragma once

class ModelInstance;
class Camera;
class StandardEffect;

class World
{
public:
	World();
	~World();

	void Update(const Time &aDeltaTime);
	void Render();

	Camera & GetCamera();

private:
	void NextModel();

	std::vector<std::shared_ptr<ModelInstance>> myObjects;

	std::unique_ptr<ModelInstance> mySkybox;

	std::unique_ptr<Camera> myCamera;

	std::shared_ptr<StandardEffect> myEffect;

	Time myTime;
	Time myCurrentModelTime;
	Time myTimePerModel;
	Time myModelTransitionTime;
	Vector3f myCameraFrom;

	size_t myCurrentModel;
};

