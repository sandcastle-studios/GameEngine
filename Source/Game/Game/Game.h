#pragma once

namespace SB
{
	class SceneManager;
	class Window;
}

class Game
{
public:
	Game();
	~Game();

	void Start();

private:
	std::unique_ptr<SB::Window> myWindow;
	std::unique_ptr<SB::SceneManager> mySceneManager;

	void Initialize();
	void ProcessMessages();
	void Update(const SB::Time &aDeltaTime);
	void Render();
	void CreatePerspective();
};
