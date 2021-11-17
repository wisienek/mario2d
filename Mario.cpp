#include "Mario.h"
#include <iostream>


Mario::Mario( float X, float Y ) {
	init(X, Y);
}

// const - nie zmienia pól klasy
void Mario::draw(RenderTarget& target, RenderStates state) const {
	target.draw( this->shape, state );
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
	if (jumping == 0) {
		// play sound
		// change animation
	}
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
		if (!obj->isCollectable()) continue;

		// blocks
		if (obj->isWalkable() && this->jumping == 1) {
			this->jumping = -1;
			obj->hit(this);
		}

	}

	// check for border col
	if (goBack == false) {
		sf::FloatRect bounds = this->bounds();
		if (bounds.left <= 0
			|| bounds.left + bounds.width >= this->boundsW
			|| bounds.top <= 0
			|| bounds.top + bounds.height >= this->boundsH)
			goBack = true;
		// stop falling
		if (this->jumping == -1 && bounds.top + bounds.height >= this->boundsH)
			this->jumping = 0;
	}

	if (goBack)
		this->shape.setPosition(this->prevPos);
}

void Mario::fire()
{
	if (this->canFire) {
		// create new instance of fire
		// direction: 1-right, -1 left
		short int direction = this->facing == true ? 1 : -1;

	}
}

void Mario::hit(Object * what){}

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
