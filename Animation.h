#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
private:
	Vector2u imgCount;
	Vector2u currentImg;

	float totalTime;
	float switchTime;

public:
	sf::IntRect uvRect;
	
	Animation(Texture* texture, Vector2u imageCount, float switchTime);
	~Animation();

	void update(int row, float deltaTime);

};

