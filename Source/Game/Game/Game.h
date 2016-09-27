#pragma once

class SceneManager;
class Window;

class Game
{
public:
	Game();
	~Game();

	void Start();

private:
	std::unique_ptr<Window> myWindow;
	std::unique_ptr<SceneManager> mySceneManager;

	void Initialize();
	void ProcessMessages();
	void Update(const Time &aDeltaTime);
	void Render();
	void CreatePerspective();
};
