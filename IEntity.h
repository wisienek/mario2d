#pragma once

#include "Object.h"

using namespace sf;

class IEntity : public Object
{
protected:
	// basic properties
	short int hp = 3;

	bool isMoving = false; // is Entity moving?
	bool canCollide = true; // Can Entity collide with sth?

	// movement
	Vector2f prevPos{ 0, 0 }; // prev pos for backing
	float veolicity{ 1.f }; // How fast can move per frame

	short int jumping{ -1 }; // Jumping state: -1 <- down, 0 <- standing, 1 <- up
	short int jumpingDuration{ 60 }; // How high can jump
	short int jumpingCounter{ 0 }; // How high already jumped

	bool facingRight = true; // Facing: true - right, false - left

	// references
	Object* walkingOn; // What the ENtity is walking on (0 / pointer)
public:
	bool isAlive = true; // Is Entity alive? - for animation etc.

	float dt{ 0.f };

	void move(Vector2f *movement);
	void setPosition(float x, float y);
	FloatRect bounds();

	virtual void resolveColision();
	std::string collisionDirection(Object *colided);
	bool collisionBelow(Object *test);

	virtual void die();
};

