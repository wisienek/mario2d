#include "Goomba.h"
#include "Animation.h"

#include <iostream>

Goomba::Goomba(float x, float y)
{
	init(x, y);
}

void Goomba::animate(float deltaTime)
{
	if (!this->isAlive) return;

	std::cout << "Goomba animation!";

	this->animation->update(0, this->dt, this->facingRight);

	this->shape.setTextureRect(this->animation->uvRect);
}

void Goomba::update()
{
	sf::Vector2f movement{ this->facingRight? 0.5f : -0.5f, 0.f };

	this->animate(this->dt);
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

