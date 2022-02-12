#include "Coin.h"
#include "Game.h"

#include <iostream>

void Coin::init(float X, float Y)
{
	this->animatedTexture.loadFromFile(this->textureFile_animation);
	this->shape.setTexture(this->animatedTexture);
	this->animation = new Animation(&this->animatedTexture, Vector2u(4, 1), 0.035f);

	this->shape.setPosition(X, Y);
}

Coin::Coin(float X, float Y)
{
	this->init(X, Y);
}

void Coin::animate(float deltaTime)
{
	this->animation->update(0, deltaTime * 0.45, 1);

	this->shape.setTextureRect(this->animation->uvRect);
}

void Coin::die()
{
	// add points
	Game *game = Game::getInstance();
	game->addPoints(500);

	// play sound
	game->getSoundManager()->playCoin();

	// remove coin
	game->removeObject(this);
}

void Coin::update() {}

void Coin::hit(Object * what, std::string direction) {}