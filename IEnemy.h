#pragma once

#include "Object.h"
#include "IEntity.h"

class IEnemy : public IEntity
{
protected:
	bool canBeJumpedOn;

public:
	short int width;
	short int height;

	bool isHurtable() { return canBeJumpedOn; };
	virtual std::string name() = 0;

	virtual void hit(Object *what, std::string direction) = 0;
	virtual void hurt() = 0;
};

