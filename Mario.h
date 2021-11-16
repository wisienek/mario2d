#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

// Mario extends SFML:: Drawable <- drawable object
class Mario : public sf::Drawable
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


	// small mario 16x16px
	const short int small_width{ 16 };
	const short int small_height{ 16 };
	// big mario 16x32px
	const short int big_width{ 16 };
	const short int big_height{ 32 };
	// current size
	short int width{ small_height };
	short int height{ small_height };

	// class config
	short int hearts = 3;
	// movement
	const float playerVelocity{ 2.0f };
	// -1 <- down, 0 <- standing, 1 <- up
	short int jumping{ 0 };
	// -1 <- left, 0 <- standing, 1 <- right
	short int direction{ 0 };
	// moving somehere ( can be (0;0) if not moving )
	Vector2f velocity{ playerVelocity * direction, playerVelocity * jumping };

	// drawing shape
	void draw(RenderTarget& target, RenderStates state) const override;

	// movement
	void update();

public:
	// x,y - default position
	Mario( float X, float Y );

	// destructuring
	Mario() = delete;
	~Mario() = default;

	// positions
	float left();
	float right();
	float top();
	float bottom();
};

