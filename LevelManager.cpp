#include "LevelManager.h"

#include "Game.h"
#include "BorderBlock.h"

#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>

using namespace nlohmann;

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

	this->initWalls();

	//std::ifstream i("file.json");
	//json j;
	//i >> j;
	


	//BorderBlock *b1 = new BorderBlock();
	//b1->init(vm.width / 3, vm.height - 40);
	//this->Objects.push_back(dynamic_cast<Object*>(b1));

	//BorderBlock *b2 = new BorderBlock();
	//b2->init(vm.width / 4, vm.height - 16);
	//this->Objects.push_back(dynamic_cast<Object*>(b2));

	//BorderBlock *b3 = new BorderBlock();
	//b3->init(vm.width / 4 - 16, vm.height - 16);
	//this->Objects.push_back(dynamic_cast<Object*>(b3));

	//BorderBlock *b4 = new BorderBlock();
	//b4->init(vm.width / 4 - 32, vm.height - 16);
	//this->Objects.push_back(dynamic_cast<Object*>(b4));

}

void LevelManager::initWalls()
{
	Game* game = Game::getInstance();
	sf::VideoMode vm = game->getVideoMode();

	int i = vm.height / 16;
	int j = vm.width / 16;

	for (int _k = 0; _k < i; _k++) {
		BorderBlock *b1 = new BorderBlock();
		b1->init(0, float(_k * 16));
		this->Objects.push_back(dynamic_cast<Object*>(b1));

		BorderBlock *b2 = new BorderBlock();
		b2->init(vm.width - 16, float(_k * 16));
		this->Objects.push_back(dynamic_cast<Object*>(b2));
	}

	for (int _k = 1; _k < j-1; _k++) {
		BorderBlock *b1 = new BorderBlock();
		b1->init(float(_k * 16), 0);
		this->Objects.push_back(dynamic_cast<Object*>(b1));

		BorderBlock *b2 = new BorderBlock();
		b2->init(float(_k * 16), vm.height - 16);
		this->Objects.push_back(dynamic_cast<Object*>(b2));
	}

}


