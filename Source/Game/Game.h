#pragma once

class Window;
class World;

class Game
{
public:
	Game();
	~Game();

	void Start();

private:
	std::unique_ptr<Window> myWindow;
	std::unique_ptr<World> myWorld;

	void Initialize();
	void ProcessMessages();
	void Update(const Time &aDeltaTime);
	void Render();
	void CreatePerspective();
};
