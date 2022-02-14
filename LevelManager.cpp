#include "LevelManager.h"

#include "Game.h"
#include "BorderBlock.h"
#include "Goomba.h"
#include "Coin.h"

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

void LevelManager::load(int level = 0)
{
	Game* game = Game::getInstance();
	sf::VideoMode vm = game->getVideoMode();

	this->initWalls();

	std::ifstream i("./levels/level" + std::to_string(level) + ".json");
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

			game->setMaxPoints( game->getMaxPoints() + Goomba::killPoints );
		}
	}

	for (auto Entity : j["collectables"]) {
		std::string name = Entity["name"]; // Entity name
		sf::Vector2i location{ Entity["location"]["x"], Entity["location"]["y"] }; // Entity location

		if (!this->isEntityNameValid(name)) continue;

		if (name == "Coin") {
			Coin *c1 = new Coin(location.x, location.y);
			this->Objects.push_back(c1);

			game->setMaxPoints( game->getMaxPoints() + Coin::killPoints );
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

bool LevelManager::isEntityNameValid(std::string name)
{
	return std::find(this->validEntities.begin(), this->validEntities.end(), name) != this->validEntities.end();
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
	else {
		for (auto it = this->Objects.begin(); it != this->Objects.end(); it++) {
			if ((*it)->id == object->id) {
				std::cout << "Removed " << *it << " element!" << std::endl;

				this->Objects.erase(it);
				delete object;
				return;
			}
		}
	}
}

bool LevelManager::objectWithinBounds(int x, int y, unsigned short int width, unsigned short int height)
{
	Game* game = Game::getInstance();

	int screenWidth = game->getVideoMode().width;
	int screenHeight = game->getVideoMode().height;

	// starting position is outside screen
	if (x >= screenWidth || y >= screenHeight) return false;
	// end of texture is outside
	if (x + width > screenWidth || y + height > screenHeight) return false;

	return true;
}

