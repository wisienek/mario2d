#include "Game.h"
#include <iostream>
#include <sstream>

#include "Mario.h"
#include "Object.h"
#include "BorderBlock.h"
//#include "LevelManager.h"

// namespace SFML
using namespace sf;
// namespace STD
using namespace std;

Game* Game::_game = nullptr;
Game* Game::getInstance() {
	if (_game == nullptr) {
		_game = new Game();
	}

	return _game;
}

const bool Game::isRunning() const
{
	return this->window->isOpen();
}

LevelManager* Game::getLevelManager() 
{
	return LevelManager::getInstance();
}

SoundManager* Game::getSoundManager()
{
	return SoundManager::getInstance();
}

std::vector<Object*> Game::getObjects()
{
	return LevelManager::getInstance()->getObjects();
}

std::vector<IEntity*> Game::getEntities()
{
	return LevelManager::getInstance()->getEntities();
}

void Game::initVars()
{
	this->window = nullptr;
	this->videoMode.height = 16 * 32;
	this->videoMode.width = 16 * 32;
}

void Game::initFont()
{
	if (!this->font.loadFromFile("./resources/fonts/SuperMarioWorldTextBoxRegular-Y86j.ttf"))
		std::cout << "Font Not loaded!" << std::endl;
}

void Game::initText()
{
	this->pointsText.setFont(this->font);
	this->pointsText.setCharacterSize(12);
	this->pointsText.setPosition(20, 18);
	this->pointsText.setFillColor(sf::Color::White);
	this->pointsText.setString("Points	" + this->points);

	this->endingText.setFont(this->font);
	this->endingText.setCharacterSize(16);
	this->endingText.setPosition(this->videoMode.width/2 - 50, this->videoMode.height/2);
	this->endingText.setFillColor(sf::Color::White);
	this->endingText.setString("GAME OVER!\nPoints:   " + this->points);
}

void Game::initWindow()
{
	this->window = new RenderWindow(this->videoMode, "Mario2D");
	this->window->setFramerateLimit(144);
}

void Game::initPlayer()
{
	this->player = new Mario(0.f, 0.f);
	this->player->setPosition(
		float(this->videoMode.width / 2), 
		float(this->videoMode.height - ((this->player->bounds().height/3) * 2) - 1)
	);
}

void Game::initBlocks()
{
	// load level 0
	this->getLevelManager()->load(0);
}

void Game::showEndingScreen()
{
	this->endingText.setString("GAME OVER!\nPoints:   " + this->points);

	this->window->draw(this->endingText);
	this->window->display();
}

// game mechanics
void Game::update()
{
	this->updateEvents();
	this->updateText();

	if (this->isGameOver()) return;

	this->updateTime();
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
	for (auto& i : this->getObjects()) {
		Object *obj = dynamic_cast<Object*>(i);
		if (!obj) continue;

		obj->update();
		obj->animate(this->deltaTime);
	}

	for (auto& i : this->getEntities()) {
		IEntity *obj = dynamic_cast<IEntity*>(i);

		if (!obj) continue;
		if (!obj->isAlive) {
			this->removeObject(obj);
			continue;
		}

		obj->update();
		obj->dt = this->deltaTime;
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

	if(this->isGameOver())
		return this->showEndingScreen();

	this->window->draw(*player);

	for (auto& i : this->getObjects()) {
		Object *obj = dynamic_cast<Object*>(i);
		if (!obj) continue;

		this->window->draw(*obj);
	}

	for (auto& i : this->getEntities()) {
		IEntity *obj = dynamic_cast<IEntity*>(i);
		if (!obj) continue;
		if (!obj->isAlive) continue;

		this->window->draw(*obj);
	}


	this->renderText();
	this->window->display();
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points	" << this->points;

	this->pointsText.setString(ss.str());
}

void Game::renderText()
{
	this->window->draw(this->pointsText);
}

void Game::removeObject(Object * object)
{
	this->getLevelManager()->removeObject(object);
}

void Game::addPoints(long _points)
{
	this->points += _points;

	if (maxPoints != 0 && this->points >= maxPoints) {
		this->getSoundManager()->gameover();
		this->state = false;
	}
}
