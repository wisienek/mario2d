#include "Game.h"
#include <iostream>

#include "Mario.h"

// namespace SFML
using namespace sf;
// namespace STD
using namespace std;

// struct/destruct
Game::Game() {
	this->initVars();
	this->initWindow();

	this->initPlayer();
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
	this->videoMode.height = 600;
	this->videoMode.width = 800;
}

void Game::initWindow()
{
	this->window = new RenderWindow(this->videoMode, "Mario2D");
	this->window->setFramerateLimit(144);
}

void Game::initPlayer()
{
	this->player = new Mario(0.f, 0.f);
	this->player->setPosition(this->videoMode.width / 2, this->videoMode.height - this->player->bounds().height - 1);

	this->player->setVideoBounds(this->videoMode.width, this->videoMode.height);
}

// game mechanics
void Game::update()
{
	this->updateEvents();
	this->updateEntities();
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

void Game::updateEntities()
{
	this->player->update();
	// auto get upper class
	for (auto& i : objects) {
		i.update();
	}
}

// visualizing
void Game::render()
{
	// drawing game
	this->window->clear(Color::Black);

	this->window->draw(*player);

	// this->window->draw(player);
	this->window->display();
}
