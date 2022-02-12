#pragma once
#include <SFML/Graphics.hpp>
#include "IEntity.h"
#include "Animation.h"

class Coin : public Object
{
private:
	String textureFile_animation = "./resources/graphics/items/coins/coin-animation.png";
	sf::Texture animatedTexture;
	Animation* animation;

	bool walkable = false;
	bool collidable = false;
	bool collectable = true;

	void init(float X, float Y);
public:
	Coin(float X, float Y);

	std::string name() { return "Coin"; };

	const static unsigned short int killPoints = 500;

	virtual void animate(float deltaTime);

	virtual void hit(Object *what, std::string direction);
	virtual void die();
	virtual void update();

	virtual void resolveColision() {};
	virtual void hurt() {};
};



