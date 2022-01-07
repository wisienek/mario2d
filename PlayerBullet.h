#pragma once

#include <SFML\Graphics.hpp>

class PlayerBullet
{
private:
	sf::Sprite shape;
	sf::Texture* texture;

public:
	PlayerBullet();
	~PlayerBullet();


	void update();
	void render();
};

