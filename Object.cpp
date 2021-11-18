#include "Object.h"

Object::Object()
{
}

// const - nie zmienia pól klasy
void Object::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->shape, state);
}
