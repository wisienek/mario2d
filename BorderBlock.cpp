#include "BorderBlock.h"

BorderBlock::BorderBlock()
{
}

BorderBlock::~BorderBlock()
{
}

void BorderBlock::init(float x, float y)
{
	this->walkable = true;
	this->collectable = false;
	this->collidable = true;

	this->blockTexture.loadFromFile(this->blockTextureSrc);
	this->shape.setTexture(this->blockTexture);
	this->shape.setPosition(x, y);
}

void BorderBlock::update()
{
}
