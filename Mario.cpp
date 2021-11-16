#include "Mario.h"

Mario::Mario( float X, float Y ) {
	// ustaw podstawow¹ pozycjê
	shape.setPosition(X, Y);
	texture.loadFromFile(textureFile_small_idle);

	shape.setTexture(texture);
}

// const - nie zmienia pól klasy
void Mario::draw(RenderTarget& target, RenderStates state) const {
	target.draw( this->shape, state );
}

void Mario::update() {

	// check for colision

	if (this->left() + velocity.x < 0)
		return;

	shape.move( velocity );
}

float Mario::left() {
	return this->shape.getPosition().x - (this->width/ 2);
}

float Mario::right() {
	return this->shape.getPosition().x + (this->width / 2);
}

float Mario::top() {
	return this->shape.getPosition().y + (this->height / 2);
}

float Mario::bottom() {
	return this->shape.getPosition().y - (this->height / 2);
}