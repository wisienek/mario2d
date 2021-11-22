#include "LevelManager.h"

#include "Game.h"
#include "BorderBlock.h"

#include <iostream>

LevelManager* LevelManager::manager = nullptr;
LevelManager* LevelManager::getInstance() {
	if (manager == nullptr) {
		manager = new LevelManager();
	}

	return manager;
}

void LevelManager::load(int level)
{
	Game* game = Game::getInstance();
	sf::VideoMode vm = game->getVideoMode();

	BorderBlock *b1 = new BorderBlock();
	b1->init(vm.width / 3, vm.height - 40);
	this->Objects.push_back(dynamic_cast<Object*>(b1));

	BorderBlock *b2 = new BorderBlock();
	b2->init(vm.width / 4, vm.height - 16);
	this->Objects.push_back(dynamic_cast<Object*>(b2));

	BorderBlock *b3 = new BorderBlock();
	b3->init(vm.width / 4 - 16, vm.height - 16);
	this->Objects.push_back(dynamic_cast<Object*>(b3));

	BorderBlock *b4 = new BorderBlock();
	b4->init(vm.width / 4 - 32, vm.height - 16);
	this->Objects.push_back(dynamic_cast<Object*>(b4));

}
