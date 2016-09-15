#pragma once

class Window;
class Scene;

class Game
{
public:
	Game();
	~Game();

	void Start();

private:
	std::unique_ptr<Window> myWindow;
	std::unique_ptr<Scene> myScene;

	void Initialize();
	void ProcessMessages();
	void Update(const Time &aDeltaTime);
	void Render();
	void CreatePerspective();
};
