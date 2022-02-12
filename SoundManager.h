#pragma once

#include <SFML/Audio.hpp>


class SoundManager
{
	SoundManager() {};
	static SoundManager* sm;

	// gameover sound
	sf::SoundBuffer gameoverBuffer;
	sf::Sound gameoverSound;

	// jumping sound
	sf::SoundBuffer jumpingBuffer;
	sf::Sound jumpingSound;

	// player dying
	sf::SoundBuffer dyingBuffer;
	sf::Sound dyingSound;

	// player -hp
	sf::SoundBuffer shrinkBuffer;
	sf::Sound shrinkSound;

	// coin sound
	sf::SoundBuffer coinBuffer;
	sf::Sound coingSound;

	// goomba ded sound
	sf::SoundBuffer goombadiedBuffer;
	sf::Sound goombadiedSound;
public:
	SoundManager(SoundManager &sm) = delete;
	void operator = (const SoundManager &) = delete;
	static SoundManager* getInstance();

	void initSounds();
	void playMarioJump();
	void playCoin();
	void goombadead();
	void playerdead();
	void playershrink();
	void gameover();
};

