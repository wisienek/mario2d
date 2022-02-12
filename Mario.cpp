#include <iostream>

#include "Mario.h"
#include "Object.h"
#include "SoundManager.h"
#include "IEnemy.h"
#include "Game.h"

Mario::Mario( float X, float Y ) {
	init(X, Y);
	this->jumping = 0;
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
			this->facingRight = false;
			this->isMoving = true;

			movement->x = -this->playerVelocity;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->facingRight = true;
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
	this->walkingOn = nullptr;

	this->shape.setPosition(X, Y);
}

void Mario::jump()
{
	if (jumping != 0 || isBouncing) return;

	this->walkingOn = 0;
	this->jumping = 1;

	SoundManager::getInstance()->playMarioJump();
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
		short int direction = this->facingRight == true ? 1 : -1;
		// new PlayerFire(this);
	}
}

void Mario::hit(Object * what, std::string direction)
{
	if (what->name() == "Goomba" && direction == "BOTTOM") {
		what->die();
		return;
	}

	IEnemy* enemy = dynamic_cast<IEnemy*>(what);
	if (enemy) {
		this->hurt();
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
	this->isAlive = false;
	Game* game = Game::getInstance();

	game->setGameOver();
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
			if (this->facingRight) {
				rect.left = 2 * rect.width;
				rect.width = abs(rect.width);
			}
			else {
				rect.left = 3 * abs(rect.width);
				rect.width = -abs(rect.width);
			}
		}
		else if (jumping == 1 && frame != 0) {
			if (this->facingRight) {
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
		this->animation->update(row, this->dt, this->facingRight);
	}

	this->shape.setTextureRect(this->animation->uvRect);
}
