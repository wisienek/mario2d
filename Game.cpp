#include "Game.h"

#include "Mario.h"

// namespace SFML
using namespace sf;
// namespace STD
using namespace std;

// struct/destruct
Game::Game(){
	this->initVars();
	this->initWindow();
}

Game::~Game() {
	delete this->window;
}

const bool Game::isRunning() const
{
	return this->window->isOpen();
}


void Game::initVars()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new RenderWindow(this->videoMode, "Mario2D");
	this->window->setFramerateLimit(120);
}

// game mechanics
void Game::update()
{
	this->updateEvents();
}

void Game::updateEvents()
{
	// event handler
	while (this->window->pollEvent( this->event )) {
		switch (event.type) {
			case Event::Closed: {
				this->window->close();
				break;
			}
			case Event::KeyPressed: {
				// which key was pressed
				switch (event.key.code) {
					case Keyboard::Escape: {
						this->window->close();
						break;
					}
				}
			}
		}
	}
}

// visualizing
void Game::render()
{
	// drawing game
	this->window->clear(Color::Black);


	// this->window->draw(player);
	this->window->display();
}
