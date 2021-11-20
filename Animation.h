#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
private:
	Vector2u imgCount;

	float totalTime;
	float switchTime;

public:
	Vector2u currentImg;

	IntRect uvRect;
	int currentRow;
	
	Animation(Texture* texture, Vector2u imageCount, float switchTime);
	~Animation();

	void update(int row, float deltaTime, bool facingRight);
};

