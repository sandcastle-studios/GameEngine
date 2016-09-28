#include "stdafx.h"
#include <Game\Game.h>
#include <Engine\Debugging\CommandLineParameters.h>

#ifdef PUBLISH
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
#else
int main(int argc, char * argv[])
#endif
{
	CommandLineParameters::CreateInstance();

	CommandLineParameters::GetInstance().Parse(argc, argv);

	Game game;
	game.Start();

	CommandLineParameters::DestroyInstance();

    return 0;
}
