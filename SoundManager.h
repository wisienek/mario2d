#pragma once

#include <SFML/Audio.hpp>


class SoundManager
{
	SoundManager() {};
	static SoundManager* sm;

	sf::SoundBuffer jumpingBuffer;
	sf::Sound jumpingSound;

public:
	SoundManager(SoundManager &sm) = delete;
	void operator = (const SoundManager &) = delete;
	static SoundManager* getInstance();


	void initSounds();
	void playMarioJump();
};

