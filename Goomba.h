#pragma once

#include <SFML/Graphics.hpp>

#include "IEnemy.h"
#include "Animation.h"

class Goomba : public IEnemy
{
private: 
	String textureFile_animation = "./resources/graphics/entities/goomba-animation.png";
	sf::Texture animatedTexture;
	Animation* animation;

	bool walkingRight = true;
	bool canBeJumpedOn = true;
	bool walkable = false;
	bool collidable = true;
	bool collectable = false;

	void init(float X, float Y);
public:
	Goomba(float x=0, float y=0);
	const static unsigned short int killPoints = 100;

	virtual std::string name() { return "Goomba"; };

	//functions
	virtual void hit(Object *what, std::string direction);
	virtual void hurt() {};
	virtual void die();

	//animation
	virtual void animate(float deltaTime);
	virtual void update();
};

