#include <iostream>
#include "Game.h"


int main()
{
	// init game
	Game game;

	// main loop
	while (game.isRunning()) {
		game.update();
		game.render();
	}

	return 0;
}
