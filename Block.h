#pragma once

#include <string>

#include "Object.h"

class Block : public Object
{
public:

	Block() {};
	~Block() {};

	virtual std::string name() { return "Block"; };

	// pass to other classes
	virtual void update() = 0;
	virtual void hurt() = 0;
	virtual void die() = 0;

	// does nothing
	virtual void hit(Object *what, std::string direction) {};
	virtual void animate() {}
	virtual void resolveColision() {};
};

