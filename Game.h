#pragma 

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Mario.h"


// game class
class Game
{
private:
	// window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	// Entities
	Mario* player;
	std::vector<Object*> objects;

	Clock clock;

	// functions
	void initVars();
	void initWindow();
	void initPlayer();
	void initBlocks();

public:
	// constr/destr
	Game();
	virtual ~Game();

	float deltaTime{ 0.f };

	// access
	const bool isRunning() const;

	// functions
	void update();
	void updateEvents();
	void updateEntities();
	void updateTime();
	void render();
};

