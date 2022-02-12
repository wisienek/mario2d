#include "Object.h"

Object::Object()
{
	static int _id = 0;
	this->id = _id++;
}

// const - nie zmienia p�l klasy
void Object::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->shape, state);
}
