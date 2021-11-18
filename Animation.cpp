#include "Animation.h"

Animation::Animation(sf::Texture * texture, sf::Vector2u imageCount, float switchTime)
{
	this->imgCount = imageCount; // how many images there are
	this->switchTime = switchTime; // how often to switch
	this->totalTime = 0.f;
	this->currentImg.x = 0;

	this->uvRect.width = texture->getSize().x / float(imageCount.x);
	this->uvRect.height = texture->getSize().y / float(imageCount.y);

}

Animation::~Animation()
{
}

// update texture
void Animation::update(int row, float deltaTime)
{
	this->currentImg.y = row;
	this->totalTime += deltaTime;

	if (this->totalTime >= this->switchTime) {
		this->totalTime -= this->switchTime;
		this->currentImg.x++;

		if (this->currentImg.x >= this->imgCount.x) {
			this->currentImg.x = 0;
		}
	}

	this->uvRect.left = this->currentImg.x * this->uvRect.width;
	this->uvRect.top = this->currentImg.y * this->uvRect.height;
}