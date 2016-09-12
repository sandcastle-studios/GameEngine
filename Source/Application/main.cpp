#include "stdafx.h"
#include <Game.h>

#ifdef PUBLISH
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
#else
int main()
#endif
{
	Game game;
	game.Start();

    return 0;
}
