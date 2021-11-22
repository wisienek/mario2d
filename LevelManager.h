#pragma once

#include <vector>

#include "Object.h"

class LevelManager
{
private:
	LevelManager() {}; // can't init manager from outside
	static LevelManager* manager;

	std::vector<Object*> Objects;

public:
	// prevent copying manager
	LevelManager(LevelManager &manager) = delete;
	void operator = (const LevelManager &) = delete;

	static LevelManager* getInstance();

	void load(int level);

	std::vector<Object*> getObjects() {
		return Objects;
	}
};

