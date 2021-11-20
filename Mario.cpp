#include <iostream>

#include "Mario.h"
#include "Object.h"

Mario::Mario( float X, float Y ) {
	init(X, Y);
}

void Mario::update() {
	sf::Vector2f movement{ 0.f, 0.f };
	this->updateKeyInput( &movement );

	// if jumping
	if (jumping == 1) {
		this->isMoving = true;
		movement.y = -this->playerVelocity * 1.3f;
		jumpingCounter += short(this->playerVelocity);

		if (jumpingCounter > jumpingDuration) {
			endJumping();
		}
	}
	// if falling
	else if (jumping == -1) {
		this->isMoving = true;
		movement.y = this->playerVelocity * 1.7f;
	}

	this->animate(this->dt);
	this->move(&movement);
	
	this->isMoving = false;
}

void Mario::updateKeyInput(sf::Vector2f *movement)
{
	if (!this->isCrouching) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->facing = false;
			this->isMoving = true;

			movement->x = -this->playerVelocity;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->facing = true;
			this->isMoving = true;

			movement->x = this->playerVelocity;
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
	this->playerTextureAnimated.loadFromFile(this->textureFile_small_animation);
	this->shape.setTexture(this->playerTextureAnimated);

	this->animation = new Animation(&this->playerTextureAnimated, Vector2u(3, 3), 0.1f);
	this->walkingOn = 0;

	this->shape.setPosition(X, Y);

	if (!this->jumpingBuffer.loadFromFile("./resources/sounds/jump-small.wav"))
		std::cout << "Couldn't load junping sound!" << std::endl;

	this->jumpingSound.setBuffer(this->jumpingBuffer);
	this->jumpingSound.setVolume(2.f);
}

void Mario::jump()
{
	if (jumping != 0 || isBouncing) return;

	this->walkingOn = 0;
	this->jumping = 1;

	this->jumpingSound.play();
}

void Mario::crouch()
{
	if (this->isBig && !this->isCrouching)
		this->isCrouching = true;
}

void Mario::endJumping()
{
	if (jumping)
	{
		jumpingCounter = 0;
		jumping = -1;
	}
}

void Mario::fire()
{
	if (this->canFire) {
		// create new instance of fire
		// direction: 1-right, -1 left
		short int direction = this->facing == true ? 1 : -1;
		// new PlayerFire(this);
	}
}

void Mario::hurt()
{
	if (this->hp - 1 < 0) 
		return this->die();
	
	this->hp -= 1;
}

void Mario::die()
{
	// set animation to dying and end game
}

void Mario::animate(float deltaTime)
{
	unsigned short int row = 0;
	if (this->isMoving == true) row = 1;
	
	// handle jumping
	if (jumping != 0) { 
		row = 2; 
		int ar = this->animation->currentRow;
		if (row != ar) {
			this->animation->currentImg.y = row;
		}

		IntRect rect = this->animation->uvRect;
		int frame = rect.left % abs(rect.width);

		if (jumping == -1 && frame != 2) {
			if (this->facing) {
				rect.left = 2 * rect.width;
				rect.width = abs(rect.width);
			}
			else {
				rect.left = 3 * abs(rect.width);
				rect.width = -abs(rect.width);
			}
		}
		else if (jumping == 1 && frame != 0) {
			if (this->facing) {
				rect.left = 0;
				rect.width = abs(rect.width);
			}
			else {
				rect.left = 1 * abs(rect.width);
				rect.width = -abs(rect.width);
			}
		}
	}
	else {
		this->animation->update(row, this->dt, this->facing);
	}

	this->shape.setTextureRect(this->animation->uvRect);
}
