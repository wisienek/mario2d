#pragma 

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Mario.h"
#include "LevelManager.h"


// game class
class Game
{
private:
	Game() {};
	static Game* _game;

	// window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	// Entities
	Mario* player;

	//LevelManager levelManager;
	std::vector<Object*> objects;

	Clock clock;
public:
	Game(Game &game) = delete;
	void operator = (const Game &) = delete;

	static Game* getInstance();

	float deltaTime{ 0.f };

	// access
	const bool isRunning() const;
	std::vector<Object*> getObjects();
	sf::RenderWindow* getWindow() { return this->window; };
	sf::VideoMode getVideoMode() { return this->videoMode; };

	// functions
	void update();
	void updateEvents();
	void updateEntities();
	void updateTime();
	void render();

	// init functions
	void initVars();
	void initWindow();
	void initPlayer();
	void initBlocks();
};

