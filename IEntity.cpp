#include "IEntity.h"
#include "Game.h"
#include "LevelManager.h"

#include <iostream>

void IEntity::move(Vector2f * movement)
{
	FloatRect b = this->bounds();
	this->prevPos = { b.left, b.top };

	this->shape.move(*movement);

	resolveColision();
}

void IEntity::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

FloatRect IEntity::bounds()
{
	IntRect t_bounds = this->shape.getTextureRect(); // Current frame texture
	FloatRect sBounds = this->shape.getGlobalBounds(); // global texture (can have a few -''-)

	sBounds.width = abs(t_bounds.width);
	sBounds.height = t_bounds.height;

	return sBounds;
}

void IEntity::setVideoBounds(const int w, const int h)
{
	this->boundsW = w;
	this->boundsH = h;
}

void IEntity::resolveColision()
{
	if (canCollide == false) return;
	bool goBack = false;

	std::vector<Object*> objects = Game::getInstance()->getObjects();

	// loop through every object
	for (auto& i : objects) {
		Object *obj = dynamic_cast<Object*>(i);
		if (!obj) continue;

		// ignore if can't collide
		if (!obj->isCollidable()) continue;

		// ignore if not collectable
		if (obj->isCollectable()) continue;

		// blocks
		if (obj->isWalkable()) {
			std::string direction = this->collisionDirection(obj);

			if (direction == "") continue;

			if (direction == "TOP") {
				if (this->jumping == -1)
					this->jumping = 0;

				this->walkingOn = obj;
			}

			if (direction == "BOTTOM" && this->jumping == 1)
				this->jumping = -1;

			obj->hit(this, direction);

			goBack = true;
		}

		goBack = true;
	}

	sf::FloatRect bounds = this->bounds();

	bool withinBounds = !(bounds.left <= 0
		|| bounds.left + abs(bounds.width) >= this->boundsW
		|| bounds.top <= 0
		|| bounds.top + bounds.height >= this->boundsH);

	//std::cout << "withinBounds: " << withinBounds << " : " << bounds.left << " | " << bounds.left + abs(bounds.width)
	//	<< " | " << bounds.top << " | " << bounds.top + bounds.height << std::endl;
	// std::cout << "Postion: " << bounds.left << " " << bounds.top << " | " << this->prevPos.x << " " << this->prevPos.y << std::endl;

	// check for border col
	if (goBack == false) {
		if (!withinBounds) {
			goBack = true;
			this->walkingOn = 0;
		}
		// stop falling
		if (this->jumping == -1 && bounds.top + bounds.height >= this->boundsH)
			this->jumping = 0;
	}

	if (goBack)
		this->shape.setPosition(this->prevPos);
	else {
		if (this->walkingOn && !collisionBelow(this->walkingOn)) {
			this->jumping = -1;
		}
	}
}

std::string IEntity::collisionDirection(Object * colided)
{
	sf::FloatRect entityBounds = this->bounds();
	sf::FloatRect colidedBounds = colided->getShape().getGlobalBounds();

	if (entityBounds.intersects(colidedBounds) == false) return "";

	float p_t = entityBounds.top;
	float p_b = entityBounds.top + entityBounds.height;
	float p_l = entityBounds.left;
	float p_r = entityBounds.left + abs(entityBounds.width);
	float p_w = abs(entityBounds.width);
	float p_h = entityBounds.height;

	float o_t = colidedBounds.top;
	float o_b = colidedBounds.top + colidedBounds.height;
	float o_l = colidedBounds.left;
	float o_r = colidedBounds.left + colidedBounds.width;
	float o_w = colidedBounds.width;
	float o_h = colidedBounds.height;

	if ((p_b > o_t && p_b < o_b - (o_h * 3 / 4)) && ((p_l > o_l && p_l < o_r) || (p_r < o_r && p_r > o_l)))
		return "TOP";
	if ((p_t > o_t + (o_h * 3 / 4) && p_t <= o_b) && ((p_l >= o_l && p_l <= o_r) || (p_r >= o_l && p_r <= o_r)))
		return "BOTTOM";
	if ((p_r > o_l && p_r < o_r) && ((p_b <= o_b && p_b >= o_t) || (p_t >= o_t && p_t <= o_b)))
		return "LEFT";
	if ((p_l > o_l && p_l < o_r) && ((p_b <= o_b && p_b >= o_t) || (p_t >= o_t && p_t <= o_b)))
		return "RIGHT";

	return "";
}

bool IEntity::collisionBelow(Object *test)
{
	if (!test) return false;

	sf::FloatRect entityBounds = this->bounds();

	float p_t = entityBounds.top;
	float p_b = entityBounds.top + entityBounds.height + 2;
	float p_l = entityBounds.left;
	float p_r = entityBounds.left + abs(entityBounds.width);

	sf::FloatRect colidedBounds = test->getShape().getGlobalBounds();
	float o_t = colidedBounds.top;
	float o_b = colidedBounds.top + colidedBounds.height;
	float o_l = colidedBounds.left;
	float o_r = colidedBounds.left + colidedBounds.width;

	bool leftWithin = (p_l >= o_l && p_l <= o_r);
	bool rightWithin = (p_r >= o_l && p_r <= o_r);
	bool botWithin = (p_b >= o_t && p_b <= o_b);

	if ((leftWithin || rightWithin) && botWithin)
		return true;

	return false;
}
