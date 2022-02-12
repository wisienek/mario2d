#pragma 

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Mario.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "IEnemy.h"


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
	sf::Font font;

	// Entities
	Mario* player;

	long points = 0;
	long maxPoints = 0;

	sf::Text pointsText;
	sf::Text endingText;

	bool state = true; // 0 - game over, 1 - playing

	Clock clock;
public:
	Game(Game &game) = delete;
	void operator = (const Game &) = delete;
	static Game* getInstance();

	float deltaTime{ 0.f };

	// access
	const bool isRunning() const;
	std::vector<Object*> getObjects();
	std::vector<IEntity*> getEntities();
	sf::RenderWindow* getWindow() { return this->window; };
	sf::VideoMode getVideoMode() { return this->videoMode; };
	LevelManager* getLevelManager();
	SoundManager* getSoundManager();

	Mario* getPlayer() {
		return this->player;
	}

	bool isGameOver() {
		return state == false;
	}
	void setGameOver() {
		state = false;
	}

	long getMaxPoints() {
		return this->maxPoints;
	}

	// functions
	void update();
	void updateEvents();
	void updateEntities();
	void updateTime();
	void render();

	void updateText();
	void renderText();

	void removeObject(Object* object);

	void addPoints(long _points);

	// init functions
	void initVars();
	void initFont();
	void initText();
	void initWindow();
	void initPlayer();
	void initBlocks();
	void showEndingScreen();
	void setMaxPoints(long _points) {
		this->maxPoints = _points;
	}
};

