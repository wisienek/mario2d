#pragma once

#include "Block.h"

class BorderBlock : public Block
{
	sf::Texture blockTexture;
	std::string blockTextureSrc = "./resources/graphics/blocks/block.png";

public:
	BorderBlock();
	~BorderBlock();

	virtual void update();
	virtual void hurt() {};
	virtual void die() {};

	void init(sf::Vector2i v);
	void init(float x=0, float y=0);
	virtual void hit() {};
	virtual void animate(float deltaTime) {}

};

