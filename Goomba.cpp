#include "Goomba.h"
#include "Animation.h"
#include "Game.h"

#include <iostream>

Goomba::Goomba(float x, float y)
{
	init(x, y);

	// set to falling on init to reset position (not to float in one axis)
	this->jumping = -1;
}

void Goomba::hit(Object * what, std::string direction)
{

}

void Goomba::die()
{
	this->isAlive = false;

	Game *game = Game::getInstance();
	game->addPoints(100);

	game->getSoundManager()->goombadead();
}

void Goomba::animate(float deltaTime)
{
	if (!this->isAlive) return;

	this->animation->update(0, deltaTime * 0.1, this->facingRight);

	this->shape.setTextureRect(this->animation->uvRect);
}

void Goomba::update()
{
	sf::Vector2f movement{ 
		this->facingRight ? 
			0.6f : -0.6f, 
		this->jumping == -1 ? 
			1.2f : 0.0f 
	};

	if (movement.x != 0 && movement.y != 0)
		this->isMoving = true;
	else
		this->isMoving = false;

	//std::cout << "jumping: " << this->jumping << " " << movement.y << std::endl;

	this->move(&movement);
}

void Goomba::init(float X, float Y)
{
	this->animatedTexture.loadFromFile(this->textureFile_animation);
	this->shape.setTexture(this->animatedTexture);
	this->animation = new Animation(&this->animatedTexture, Vector2u(2, 1), 0.035f);
	
	this->walkingOn = nullptr;

	this->shape.setPosition(X, Y);

	this->canBeJumpedOn = true;
	this->isMoving = true;
	this->hp = 1;
}

