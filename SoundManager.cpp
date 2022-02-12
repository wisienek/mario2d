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
	// gameover sound
	if (!this->gameoverBuffer.loadFromFile("./resources/sounds/gameover.wav"))
		std::cout << "Couldn't load gameover sound!" << std::endl;

	this->gameoverSound.setBuffer(this->gameoverBuffer);
	this->gameoverSound.setVolume(3.f);

	// dying sound
	if (!this->dyingBuffer.loadFromFile("./resources/sounds/death.wav"))
		std::cout << "Couldn't load dying sound!" << std::endl;

	this->dyingSound.setBuffer(this->dyingBuffer);
	this->dyingSound.setVolume(3.f);

	// shrinking sound
	if (!this->shrinkBuffer.loadFromFile("./resources/sounds/shrink.wav"))
		std::cout << "Couldn't load shrink sound!" << std::endl;

	this->shrinkSound.setBuffer(this->shrinkBuffer);
	this->shrinkSound.setVolume(2.f);

	// jump sound
	if (!this->jumpingBuffer.loadFromFile("./resources/sounds/jump-small.wav"))
		std::cout << "Couldn't load junping sound!" << std::endl;

	this->jumpingSound.setBuffer(this->jumpingBuffer);
	this->jumpingSound.setVolume(2.f);

	// coin sound
	if (!this->coinBuffer.loadFromFile("./resources/sounds/coin.wav"))
		std::cout << "Couldn't load coin sound!" << std::endl;

	this->coingSound.setBuffer(this->coinBuffer);
	this->coingSound.setVolume(2.5f);

	// goomba died sound

	if (!this->goombadiedBuffer.loadFromFile("./resources/sounds/stomp.wav"))
		std::cout << "Couldn't load goomba dying sound!" << std::endl;

	this->goombadiedSound.setBuffer(this->goombadiedBuffer);
	this->goombadiedSound.setVolume(2.5f);
}

void SoundManager::playMarioJump()
{
	this->jumpingSound.play();
}

void SoundManager::playCoin()
{
	this->coingSound.play();
}

void SoundManager::goombadead()
{
	this->goombadiedSound.play();
}

void SoundManager::playerdead()
{
	this->dyingSound.play();
}

void SoundManager::playershrink()
{
	this->shrinkSound.play();
}

void SoundManager::gameover()
{
	this->gameoverSound.play();
}

