#pragma once

class ModelInstance;
class Camera;
class StandardEffect;
class RenderTexture;

class World
{
public:
	World();
	~World();

	void Update(const Time &aDeltaTime);
	void Render();

	Camera & GetCamera();

private:
	std::vector<std::shared_ptr<ModelInstance>> myObjects;

	std::unique_ptr<ModelInstance> mySkybox;
	std::unique_ptr<ModelInstance> myAssimpModel;

	std::shared_ptr<RenderTexture> myRenderTexture;

	std::unique_ptr<Camera> myCamera;

	std::shared_ptr<StandardEffect> myEffect;

	Time myTime;
};

