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

	if (jumping == 1) {
		this->move(0.f, -this->playerVelocity * 1.3);
		jumpingCounter += this->playerVelocity;

		if (jumpingCounter > jumpingDuration) {
			endJumping();
		}
	}
	else if (jumping == -1) {
		this->move(0.f, this->playerVelocity * 1.7);
	}
}

void Mario::updateKeyInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->move(-this->playerVelocity, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->move(this->playerVelocity, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->jump();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->crouch();
	}
}

void Mario::init(float X, float Y)
{
	this->shape.setPosition(X, Y);
	this->texture.loadFromFile(textureFile_small_idle);
	this->shape.setTexture(texture);
}

sf::FloatRect Mario::bounds()
{
	return this->shape.getGlobalBounds();
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
	if (jumping != 0) return;

	startJumping();
	if (jumping == 0) {
		// play sound
	}
}

void Mario::crouch()
{
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

void Mario::setVideoBounds(float w, float h)
{
	this->boundsW = w;
	this->boundsH = h;
}

void Mario::resolveColision()
{
	if (canCollide == false) return;

	bool goBack = false;

	// loop through every object
	


	// check for border col
	sf::FloatRect bounds = this->bounds();
	if (bounds.left <= 0
		|| bounds.left + bounds.width >= this->boundsW
		|| bounds.top <= 0
		|| bounds.top + bounds.height >= this->boundsH)
		goBack = true;

	// stop falling
	if (this->jumping == -1 && bounds.top + bounds.height >= this->boundsH)
		this->jumping = 0;

	if (goBack)
		this->shape.setPosition(this->prevPos);
}

void Mario::hit(Object * what)
{
}

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
