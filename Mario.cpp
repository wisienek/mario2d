#include <iostream>

#include "Mario.h"

Mario::Mario( float X, float Y ) {
	init(X, Y);
}

void Mario::update() {
	this->updateKeyInput();

	// if jumping
	if (jumping == 1) {
		this->move(0.f, -this->playerVelocity * 1.3f);
		jumpingCounter += short(this->playerVelocity);

		if (jumpingCounter > jumpingDuration) {
			endJumping();
		}
	}
	// if falling
	else if (jumping == -1) {
		this->move(0.f, this->playerVelocity * 1.7f);
	}
}

void Mario::updateKeyInput()
{
	if (!this->isCrouching) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->facing = false;
			this->isMoving = true;

			this->move(-this->playerVelocity, 0.f);
			
			this->isMoving = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->facing = true;
			this->isMoving = true;

			this->move(this->playerVelocity, 0.f);

			this->isMoving = false;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->jump();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->isMoving = false;
			this->crouch();
		}
	}
	else if (this->isCrouching && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->isCrouching = false;
	}
}

void Mario::init(float X, float Y)
{
	this->shape.setPosition(X, Y);
	this->playerTexture.loadFromFile(textureFile_small_idle);
	this->shape.setTexture(this->playerTexture);

	this->animation = new Animation(&this->playerTexture, Vector2u(3, 1), 0.3f);
	this->walkingOn = 0;
}

sf::FloatRect Mario::bounds()
{
	return this->shape.getGlobalBounds();
}

void Mario::setObjectsReference(std::vector<Object*>* objects)
{
	this->objects = objects;
}

void Mario::move(float x, float y)
{
	this->prevPos = { this->shape.getPosition().x, this->shape.getPosition().y };

	this->shape.move(x, y);
	resolveColision();
}

void Mario::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

void Mario::jump()
{
	if (jumping != 0 || isBouncing) return;

	startJumping();
	this->walkingOn = 0;

	// play sound
	// change animation
}

void Mario::crouch()
{
	this->isCrouching = true;
}

void Mario::startJumping()
{
	if (this->jumping == 0) {
		jumping = 1;
	}
}

void Mario::endJumping()
{
	if (jumping)
	{
		jumpingCounter = 0;
		jumping = -1;
	}
}

void Mario::setVideoBounds(const int w, const int h)
{
	this->boundsW = w;
	this->boundsH = h;
}

void Mario::resolveColision()
{
	if (canCollide == false) return;
	bool goBack = false;

	// loop through every object
	for (auto& i : *this->objects) {
		Object *obj = dynamic_cast<Object*>(i);
		if (!obj) continue;

		// ignore if can't collide
		if (!obj->isCollidable()) continue;

		// ignore if not collectable
		if (obj->isCollectable()) continue;

		// blocks
		if (obj->isWalkable()) {
			std::string direction = this->collisionDirection(obj);

			//if (direction == "" || direction == "TOP") {
			//	bool isBelowPlayer = collisionBelow(obj);
			//	if (isBelowPlayer)
			//		sthBelow = true;
			//}

			if (direction == "") continue;

			if (direction == "TOP") {
				if(this->jumping == -1)
					this->jumping = 0;

				this->walkingOn = obj;
			}

			if(direction == "BOTTOM" && this->jumping == 1)
				this->jumping = -1;

			obj->hit(this, direction);

			goBack = true;
		}

		goBack = true;
	}

	sf::FloatRect bounds = this->bounds();

	bool withinBounds = !(bounds.left <= 0
		|| bounds.left + bounds.width >= this->boundsW
		|| bounds.top <= 0
		|| bounds.top + bounds.height >= this->boundsH);

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

std::string Mario::collisionDirection(Object* colided)
{
	sf::FloatRect playerBounds = this->bounds();
	sf::FloatRect colidedBounds = colided->getShape().getGlobalBounds();
	
	if (playerBounds.intersects(colidedBounds) == false) return "";

	float p_t = playerBounds.top;
	float p_b = playerBounds.top + playerBounds.height;
	float p_l = playerBounds.left;
	float p_r = playerBounds.left + playerBounds.width;
	float p_w = playerBounds.width;
	float p_h = playerBounds.height;

	float o_t = colidedBounds.top;
	float o_b = colidedBounds.top + colidedBounds.height;
	float o_l = colidedBounds.left;
	float o_r = colidedBounds.left + colidedBounds.width;
	float o_w = colidedBounds.width;
	float o_h = colidedBounds.height;

	if ((p_b > o_t && p_b < o_b - (o_h/3)) && ((p_l >= o_l && p_l <= o_r) || (p_r <= o_r && p_r >= o_l)) )
		return "TOP";
	if ((p_t > o_t && p_t < o_b) && (p_l >= o_l && p_l <= o_r))
		return "BOTTOM";
	if ((p_r > o_l && p_r < o_r) && ( (p_b <= o_b && p_b >= o_t) || ( p_t >= o_t && p_t <= o_b ) ))
		return "LEFT";
	if ((p_l > o_l && p_l < o_r) && ((p_b <= o_b && p_b >= o_t) || (p_t >= o_t && p_t <= o_b)))
		return "RIGHT";

	return "";
}

bool Mario::collisionBelow(Object* test)
{
	if (!test) return false;

	sf::FloatRect playerBounds = this->bounds();

	float p_t = playerBounds.top;
	float p_b = playerBounds.top + playerBounds.height + 2;
	float p_l = playerBounds.left;
	float p_r = playerBounds.left + playerBounds.width;

	sf::FloatRect colidedBounds = test->getShape().getGlobalBounds();
	float o_t = colidedBounds.top;
	float o_b = colidedBounds.top + colidedBounds.height;
	float o_l = colidedBounds.left;
	float o_r = colidedBounds.left + colidedBounds.width;

	bool leftWithin = (p_l >= o_l && p_l <= o_r);
	bool rightWithin = (p_r >= o_l && p_r <= o_r);
	bool botWithin = (p_b >= o_t && p_b <= o_b);

	// std::cout << "left: " << leftWithin << ", Right: " << rightWithin << ", bot: " << botWithin << std::endl;
	if ((leftWithin || rightWithin) && botWithin)
		return true;

	return false;
}

void Mario::fire()
{
	if (this->canFire) {
		// create new instance of fire
		// direction: 1-right, -1 left
		short int direction = this->facing == true ? 1 : -1;

	}
}

void Mario::hit(Object * what, std::string direction){}

void Mario::hurt()
{
	if (this->hearts - 1 < 0) {
		this->die();
		return;
	}
	this->hearts -= 1;
}

void Mario::die()
{
}

void Mario::animate()
{
}
