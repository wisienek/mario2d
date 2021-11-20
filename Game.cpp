#include "Game.h"
#include <iostream>

#include "Mario.h"
#include "Object.h"
#include "BorderBlock.h"

// namespace SFML
using namespace sf;
// namespace STD
using namespace std;

// struct/destruct
Game::Game() {
	this->initVars();
	this->initWindow();

	this->initPlayer();
	this->initBlocks();
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
	this->player->setPosition(float(this->videoMode.width / 2), float(this->videoMode.height - (this->player->bounds().height/3) - 1));

	this->player->setVideoBounds(this->videoMode.width, this->videoMode.height);
	this->player->setObjectsReference(&this->objects);
}

void Game::initBlocks()
{
	BorderBlock *b1 = new BorderBlock();
	b1->init(this->videoMode.width / 3, this->videoMode.height - 40);
	this->objects.push_back( dynamic_cast<Object*>(b1) );

	BorderBlock *b2 = new BorderBlock();
	b2->init(this->videoMode.width / 4, this->videoMode.height - 16);
	this->objects.push_back(dynamic_cast<Object*>(b2));

	BorderBlock *b3 = new BorderBlock();
	b3->init(this->videoMode.width / 4 - 16, this->videoMode.height - 16);
	this->objects.push_back(dynamic_cast<Object*>(b3));

	BorderBlock *b4 = new BorderBlock();
	b4->init(this->videoMode.width / 4 - 32, this->videoMode.height - 16);
	this->objects.push_back(dynamic_cast<Object*>(b4));
}

// game mechanics
void Game::update()
{
	this->updateTime();
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
	this->player->dt = this->deltaTime;

	// auto get upper class
	for (auto& i : objects) {
		Object *obj = dynamic_cast<Object*>(i);
		if (!obj) continue;

		obj->update();
		obj->animate(this->deltaTime);
	}
}

void Game::updateTime()
{
	this->deltaTime = this->clock.restart().asSeconds();
}

// visualizing
void Game::render()
{
	// drawing game
	this->window->clear(Color::Black);

	this->window->draw(*player);

	for (auto& i : this->objects) {
		Object *obj = dynamic_cast<Object*>(i);
		if (!obj) continue;

		this->window->draw(*obj);
	}

	this->window->display();
}
