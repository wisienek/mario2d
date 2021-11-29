#include "SoundManager.h"

#include <iostream>

SoundManager* SoundManager::sm = nullptr;
SoundManager* SoundManager::getInstance()
{
	if (sm == nullptr) {
		sm = new SoundManager();
	}

	return sm;
}

void SoundManager::initSounds()
{
	if (!this->jumpingBuffer.loadFromFile("./resources/sounds/jump-small.wav"))
		std::cout << "Couldn't load junping sound!" << std::endl;

	this->jumpingSound.setBuffer(this->jumpingBuffer);
	this->jumpingSound.setVolume(2.f);

}

void SoundManager::playMarioJump()
{
	this->jumpingSound.play();
}
