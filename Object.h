#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Object : public sf::Drawable
{
protected:
	sf::Sprite shape;
	bool walkable;
	bool collidable;
	bool collectable;

	// drawing shape
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
public:
	unsigned int id;
	Object();

	bool isWalkable() { return walkable; };
	bool isCollidable() { return collidable; };
	bool isCollectable() { return collectable; };

	sf::Sprite getShape() { return shape; };

	virtual std::string name() = 0;

	virtual void update() = 0;

	// animation
	virtual void animate(float deltaTime) = 0;
	// colisions
	virtual void resolveColision() = 0;

	virtual void hit(Object *what, std::string direction) = 0; // *what <- hit this object
	virtual void hurt() = 0;
	virtual void die() = 0;
};

