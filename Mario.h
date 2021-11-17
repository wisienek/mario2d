#pragma once

#include "Object.h"

using namespace sf;

// Mario extends SFML:: Drawable <- drawable object
class Mario : public Object
{
private:
	// sprite config
	Sprite shape;
	Texture texture;
	// animation textures
	String textureFile_small_idle = "./resources/graphics/entities/mario-small-stand.png";
	String textureFile_small_run = "./resources/graphics/entities/mario-small-run.png";
	String textureFile_small_walk_0 = "./resources/graphics/entities/mario-small-walk-0.png";
	String textureFile_small_walk_1 = "./resources/graphics/entities/mario-small-walk-1.png";
	String textureFile_small_walk_2 = "./resources/graphics/entities/mario-small-walk-2.png";
	String textureFile_small_jump = "./resources/graphics/entities/mario-small-jump.png";
	String textureFile_small_fall = "./resources/graphics/entities/mario-small-fall.png";
	String textureFile_small_hang_0 = "./resources/graphics/entities/mario-small-hang-0.png";
	String textureFile_small_hang_1 = "./resources/graphics/entities/mario-small-hang-1.png";

	Vector2f prevPos{0, 0};
	// small mario 16x16px
	const short int small_width{ 16 };
	const short int small_height{ 16 };
	// big mario 16x32px
	const short int big_width{ 16 };
	const short int big_height{ 32 };
	// current size
	short int width{ small_height };
	short int height{ small_height };
	float boundsW;
	float boundsH;

	// class config
	bool isBig = false;
	bool canFire = false;
	bool isBouncing = false;
	bool isRunning = false;
	bool isCrouching = false;
	bool canCollide = true;
	
	short int hearts = 3;
	// movement
	const float playerVelocity{ 1.3f };
	// -1 <- down, 0 <- standing, 1 <- up
	short int jumping{ 0 };
	short int jumpingDuration{ 60 };
	short int jumpingCounter{ 0 };
	// -1 <- left, 0 <- standing, 1 <- right
	short int direction{ 0 };
	// moving somehere ( can be (0;0) if not moving )
	Vector2f velocity{ playerVelocity * direction, playerVelocity * jumping };

	// drawing shape
	void draw(RenderTarget& target, RenderStates state) const override;

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
	void move( float x, float y );
	void setPosition(float x, float y);
	
	void jump();
	void crouch();
	// can be in base class of entity
	void startJumping(); 
	void endJumping();

	// collisions
	void setVideoBounds(float w, float h);
	virtual void resolveColision();

	virtual void hit(Object *what);
	virtual void hurt();
	virtual void die();

	//animation
	virtual void animate();
};

