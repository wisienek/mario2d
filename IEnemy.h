#pragma once
#include "Object.h"

class IEnemy : public Object
{
protected:
	bool canBeJumpedOn;

public:
	IEnemy();

	short int width;
	short int height;

	bool isHurtable() { return canBeJumpedOn; };
	virtual std::string name() = 0;

	virtual void hit(Object *what) = 0;
	virtual void hurt() = 0;
};

