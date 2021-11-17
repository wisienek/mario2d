#pragma once
#include <SFML/Graphics.hpp>

#include <string>

class Object : public sf::Drawable
{
protected:
	bool walkable;
	bool collidable;
public:
	Object();

	bool isWalkable() { return walkable; };
	bool isCollidable() { return collidable; };

	virtual std::string name() = 0;

	virtual void update() = 0;

	// animation
	virtual void animate() = 0;
	// colisions
	virtual void resolveColision() = 0;

	virtual void hit(Object *what) = 0;
	virtual void hurt() = 0;
	virtual void die() = 0;
};

