#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "Object.h"
#include "Animation.h"

using namespace sf;

// Mario extends SFML:: Drawable <- drawable object
class Mario : public Object
{
private:
	// animation textures
	// String basetxt = "./resources/graphics/entities/mario-small-stand.png";
	String textureFile_small_animation = "./resources/graphics/entities/mario-small-animation.png";
	Texture playerTextureAnimated;
	Animation* animation;


	// fix these !!!!
	// small mario 16x16px
	const short unsigned int small_width{ 16 };
	const short unsigned int small_height{ 16 };
	// big mario 16x32px
	const short unsigned int big_width{ 16 };
	const short unsigned int big_height{ 32 };
	// current size
	short unsigned int width{ small_height };
	short unsigned int height{ small_height };
	unsigned int boundsW;
	unsigned int boundsH;

	// class config
	bool isBig = false;
	bool isBouncing = false;
	bool isCrouching = false;
	bool isMoving = false;
	bool canFire = false;
	bool canCollide = true;
	
	// game system
	short int hearts = 3;
	long points = 0;

	// movement
	Vector2f prevPos{ 0, 0 };
	const float playerVelocity{ 1.3f };
	// -1 <- down, 0 <- standing, 1 <- up
	short int jumping{ 0 };
	short int jumpingDuration{ 60 };
	short int jumpingCounter{ 0 };
	
	bool facing = true; // Facing: true - right, false - left

	// references
	std::vector<Object*>* objects;
	Object* walkingOn;

	// movement
	void updateKeyInput(Vector2f *movement);
	void init(float X, float Y);
public:
	// x,y - default position
	Mario( float X=0, float Y=0 );

	float dt{ 0.f };

	// destructuring
	Mario() = delete;
	~Mario() = default;

	virtual std::string name() { return "Mario"; };
	virtual void update();

	// positions
	sf::FloatRect bounds();
	void setObjectsReference(std::vector<Object*>* objects);
	void move(Vector2f *movement);
	void setPosition(float x, float y);
	
	void jump();
	void crouch();
	// can be in base class of entity
	void endJumping();

	// collisions
	void setVideoBounds(const int w, const int h);
	virtual void resolveColision();
	std::string collisionDirection(Object* colided);
	bool collisionBelow(Object* test);

	//functions
	void fire();
	virtual void hit(Object *what, std::string direction);
	virtual void hurt();
	virtual void die();

	//animation
	virtual void animate(float deltaTime);
};

