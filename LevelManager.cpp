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

	std::ifstream i("./levels/level1.json");
	json j;
	i >> j;
	
	// read blocks from file
	for (auto Block : j["blocks"]) {
		// { name, location{x,y} };
		std::string name = Block["name"];
		sf::Vector2i location{ Block["location"]["x"], Block["location"]["y"] };

		// swtich/case name
		BorderBlock *b1 = new BorderBlock();
		b1->init( location );
		this->Objects.push_back(dynamic_cast<Object*>(b1));
	}
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


