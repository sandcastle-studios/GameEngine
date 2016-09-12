#pragma once

class DXRenderer;

class Engine
{
public:
	DXRenderer & GetRenderer();

	static void CreateInstance();
	static Engine & GetInstance();
	static void DestroyInstance();

private:
	Engine();
	~Engine();

	std::unique_ptr<DXRenderer> myRenderer;

	static Engine * ourInstance;
};

inline Engine & Engine::GetInstance()
{
	assert("Engine not created" && ourInstance != nullptr);
	return *ourInstance;
}

inline DXRenderer & Engine::GetRenderer()
{
	return *myRenderer;
}
