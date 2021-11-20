#include <iostream>
#include "Game.h"


int main()
{
	Game* game = Game::getInstance();

	game->initVars();
	game->initWindow();

	game->initBlocks();
	game->initPlayer();

	while (game->isRunning()) {
		game->update();
		game->render();
	}

	return 0;
}
