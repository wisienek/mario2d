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
	// sprite config
	Sprite shape;
	Texture playerTexture;
	// animation textures
	String textureFile_small_idle = "./resources/graphics/entities/mario-small-stand.png";
	Animation* animation;

	// small mario 16x16px
	const short int small_width{ 16 };
	const short int small_height{ 16 };
	// big mario 16x32px
	const short int big_width{ 16 };
	const short int big_height{ 32 };
	// current size
	short int width{ small_height };
	short int height{ small_height };
	int boundsW;
	int boundsH;

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

	// drawing shape
	void draw(RenderTarget& target, RenderStates state) const override;

	// references
	std::vector<Object*>* objects;

	// movement
	void updateKeyInput();
	void init(float X, float Y);
public:
	// x,y - default position
	Mario( float X=0, float Y=0 );

	// destructuring
	Mario() = delete;
	~Mario() = default;

	virtual std::string name() { return "Mario"; };
	virtual void update();

	// positions
	sf::FloatRect bounds();
	void setObjectsReference(std::vector<Object*>* objects);
	void move( float x, float y );
	void setPosition(float x, float y);
	
	void jump();
	void crouch();
	// can be in base class of entity
	void startJumping(); 
	void endJumping();

	// collisions
	void setVideoBounds(const int w, const int h);
	virtual void resolveColision();

	//functions
	void fire();
	virtual void hit(Object *what);
	virtual void hurt();
	virtual void die();

	//animation
	virtual void animate();
};

