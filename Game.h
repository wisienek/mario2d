#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


// game class
class Game
{
private:
	// window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	void initVars();
	void initWindow();

public:
	// constr/destr
	Game();
	virtual ~Game();

	// access
	const bool isRunning() const;

	// functions
	void update();
	void updateEvents();
	void render();
};

