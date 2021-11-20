#include <iostream>

#include "Mario.h"

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
	//change texture files to small/big
	//load textures
	this->playerTextureAnimated.loadFromFile(this->textureFile_small_animation);
	this->shape.setTexture(this->playerTextureAnimated);

	this->animation = new Animation(&this->playerTextureAnimated, Vector2u(3, 3), 0.1f);
	this->walkingOn = 0;

	this->shape.setPosition(X, Y);
}

sf::FloatRect Mario::bounds()
{

	IntRect t_bounds = this->shape.getTextureRect();
	FloatRect sBounds = this->shape.getGlobalBounds();

	//sBounds.top = sBounds.top;
	//sBounds.left -= t_bounds.left;
	sBounds.width = abs(t_bounds.width);
	sBounds.height = t_bounds.height;

	return sBounds;
}

void Mario::setObjectsReference(std::vector<Object*>* objects)
{
	this->objects = objects;
}

void Mario::move(Vector2f *movement)
{
	FloatRect b = this->bounds();
	this->prevPos = { b.left, b.top };

	this->shape.move(*movement);

	resolveColision();
}

void Mario::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

void Mario::jump()
{
	if (jumping != 0 || isBouncing) return;

	this->walkingOn = 0;
	this->jumping = 1;

	// play sound
}

void Mario::crouch()
{
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

std::string Mario::collisionDirection(Object* colided)
{
	sf::FloatRect playerBounds = this->bounds();
	sf::FloatRect colidedBounds = colided->getShape().getGlobalBounds();
	
	if (playerBounds.intersects(colidedBounds) == false) return "";

	float p_t = playerBounds.top;
	float p_b = playerBounds.top + playerBounds.height;
	float p_l = playerBounds.left;
	float p_r = playerBounds.left + abs(playerBounds.width);
	float p_w = abs(playerBounds.width);
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
	float p_r = playerBounds.left + abs(playerBounds.width);

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
