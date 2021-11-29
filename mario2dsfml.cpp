#include <iostream>
#include "Game.h"


int main()
{
	Game* game = Game::getInstance();
	SoundManager* sm = SoundManager::getInstance();

	game->initVars();
	game->initWindow();

	game->initBlocks();
	game->initPlayer();

	game->initFont();
	game->initText();

	sm->initSounds();

	while (game->isRunning()) {
		game->update();
		game->render();
	}

	return 0;
}
