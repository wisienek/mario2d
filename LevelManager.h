#pragma once

#include <vector>

#include "Object.h"
#include "IEntity.h"

class LevelManager
{
private:
	LevelManager() {}; // can't init manager from outside
	static LevelManager* manager;

	std::vector<Object*> Objects;
	std::vector<IEntity*> Entities;

	std::vector<std::string> validBlocks{ "BorderBlock" };
	std::vector<std::string> validEnemies{ "Goomba" };
public:
	// prevent copying manager
	LevelManager(LevelManager &manager) = delete;
	void operator = (const LevelManager &) = delete;

	static LevelManager* getInstance();

	void load(int level);
	void initWalls();

	bool isBlockNameValid(std::string name); // check if block's name is on the list
	bool isEnemyNameValid(std::string name); // check if block's name is on the list

	std::vector<Object*> getObjects() {
		return Objects;
	}

	std::vector<IEntity*> getEntities() {
		return Entities;
	}
};

