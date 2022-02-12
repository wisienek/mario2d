#include "IEntity.h"
#include "Game.h"
#include "LevelManager.h"

#include <iostream>

void IEntity::move(Vector2f * movement)
{
	if (this->isAlive == false) return;

	if (movement->x == 0 && movement->y == 0)
		return;

	// std::cout << "Movement: " << this->name() << " " << movement->x << " " << movement->y << std::endl;

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

	sBounds.width = float(abs(t_bounds.width));
	sBounds.height = float(t_bounds.height);

	return sBounds;
}

void IEntity::resolveColision()
{
	if (this->canCollide == false) return;
	bool goBack = false;

	std::vector<Object*> objects = Game::getInstance()->getObjects();
	std::vector<IEntity*> entities = Game::getInstance()->getEntities();

	objects.insert(objects.end(), entities.begin(), entities.end());

	if (this->name() != "Mario")
		objects.push_back(dynamic_cast<Object*>(Game::getInstance()->getPlayer()));

	// loop through every object
	for (auto& i : objects) {
		Object *obj = dynamic_cast<Object*>(i);
		if (!obj) continue;

		if (obj->name() != "Mario" && obj->name() != "Coin") {
			// ignore if can't collide
			if (!obj->isCollidable()) continue;
		}

		std::string direction = this->collisionDirection(obj);
		if (obj->name() == "Coin" && direction != "") {
			obj->die();
			continue;
		}

		//std::cout << "Direction: " << direction << std::endl;

		if (direction == "") continue;

		if (direction == "TOP") {
			if (this->jumping == -1)
				this->jumping = 0;

			if(obj->isWalkable())
				this->walkingOn = obj;
		}

		if (direction == "BOTTOM" && this->jumping == 1) {
			this->jumping = -1;
		}

		obj->hit(this, direction);

		goBack = true;
	}

	sf::FloatRect bounds = this->bounds();

	unsigned int boundsW = Game::getInstance()->getVideoMode().width;
	unsigned int boundsH = Game::getInstance()->getVideoMode().height;

	// doesn't go outside screen
	bool withinBounds = !(bounds.left <= 0
		|| bounds.left + abs(bounds.width) >= boundsW
		|| bounds.top <= 0
		|| bounds.top + bounds.height >= boundsH);

	// std::cout << "withinBounds: " << withinBounds << " : " << bounds.left << " | " << bounds.left + abs(bounds.width)
	//	<< " | " << bounds.top << " | " << bounds.top + bounds.height << std::endl;
	// std::cout << "Postion: " << bounds.left << " " << bounds.top << " | " << this->prevPos.x << " " << this->prevPos.y << std::endl;

	// check for border col
	if (goBack == false) {
		if (!withinBounds) {
			goBack = true;
			this->walkingOn = 0;
		}
		// stop falling
		if (this->jumping == -1 && bounds.top + bounds.height >= boundsH)
			this->jumping = 0;
	}

	// std::cout << "Colided: " << goBack << std::endl;

	if (goBack) {
		if (this->name() == "Goomba") {
			this->facingRight = !this->facingRight;
		}

		this->shape.setPosition(this->prevPos);
	}
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

	bool entityIntersects = entityBounds.intersects(colidedBounds);
	if (entityIntersects == false) return "";

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

	if ((p_b > o_t && p_b < o_b - (o_h * 2 / 3)) && ((p_l > o_l && p_l < o_r) || (p_r < o_r && p_r > o_l)))
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

void IEntity::die()
{
	this->isAlive = false;
}
