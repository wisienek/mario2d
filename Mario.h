#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Object.h"
#include "IEntity.h"
#include "Animation.h"

using namespace sf;

// Mario extends SFML:: Drawable <- drawable object
class Mario : public IEntity
{
private:
	// animation textures
	// String basetxt = "./resources/graphics/entities/mario-small-stand.png";
	String textureFile_small_animation = "./resources/graphics/entities/mario-small-animation.png";
	Texture playerTextureAnimated;
	Animation* animation;

	// sounds
	sf::SoundBuffer jumpingBuffer;
	sf::Sound jumpingSound;

	// class config
	bool isBig = false;
	bool isBouncing = false;
	bool isCrouching = false;
	bool canFire = false;
	
	// game system
	long points = 0;

	// movement
	const float playerVelocity{ 1.3f };

	// movement functions
	void updateKeyInput(Vector2f *movement);

	void init(float X, float Y);
public:
	// x,y - default position
	Mario( float X=0, float Y=0 );

	// destroying default constructors
	Mario() = delete;
	~Mario() = default;

	virtual std::string name() { return "Mario"; };
	virtual void update();

	// movement
	void jump();
	void crouch();
	// can be in base class of entity
	void endJumping();


	//functions
	void fire();
	virtual void hit(Object *what, std::string direction) {};
	virtual void hurt();
	virtual void die();

	//animation
	virtual void animate(float deltaTime);


	long getPoints() { return this->points; };
};

