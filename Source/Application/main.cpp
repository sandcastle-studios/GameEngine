#include "stdafx.h"
#include <Game\Game.h>
#include <Engine\Debugging\CommandLineParameters.h>

#ifdef PUBLISH
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
#else
int main(int argc, char * argv[])
#endif
{
	SB::CommandLineParameters::CreateInstance();

	SB::CommandLineParameters::GetInstance().Parse(argc, argv);

	Game game;
	game.Start();

	SB::CommandLineParameters::DestroyInstance();

    return 0;
}
