#include "LevelManager.h"

#include "Game.h"
#include "BorderBlock.h"
#include "Goomba.h"

#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>
#include <algorithm>

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
		std::string name = Block["name"]; // block's name
		sf::Vector2i location{ Block["location"]["x"], Block["location"]["y"] }; // block's location

		if (!this->isBlockNameValid(name)) continue;

		if (name == "BorderBlock") {
			BorderBlock *b1 = new BorderBlock();
			b1->init(location);
			this->Objects.push_back(dynamic_cast<Object*>(b1));
		}
	}

	for (auto Enemy : j["enemies"]) {
		std::string name = Enemy["name"]; // Enemy name
		sf::Vector2i location{ Enemy["location"]["x"], Enemy["location"]["y"] }; // Enemy location

		if (!this->isEnemyNameValid(name)) continue;

		if (name == "Goomba") {
			Goomba *g1 = new Goomba(location.x, location.y);
			this->Entities.push_back(dynamic_cast<IEntity*>(g1));
		}
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

bool LevelManager::isBlockNameValid(std::string name)
{
	return std::find(this->validBlocks.begin(), this->validBlocks.end(), name) != this->validBlocks.end();
}

bool LevelManager::isEnemyNameValid(std::string name)
{
	return std::find(this->validEnemies.begin(), this->validEnemies.end(), name) != this->validEnemies.end();
}

void LevelManager::removeObject(Object * object)
{
	IEntity* ent = dynamic_cast<IEntity*>(object);
	
	if (ent) {
		for (auto it = this->Entities.begin(); it != this->Entities.end(); it++) {
			if ((*it)->id == ent->id){
				std::cout << "Removed " << *it << " element!" << std::endl;

				this->Entities.erase(it);
				delete object;
				return;
			}
		}
	}
}

