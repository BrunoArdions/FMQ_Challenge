#include "main_menu.h"
#include "game.h"
#include <iostream>

void main_menu::Initialize(sf::RenderWindow* window) {
	//initialise selected value to play the game
	this->selected = 0;

	//load the font and display text
	this->font = new sf::Font();
	this->font->loadFromFile("gamefont.ttf");

	/*MAIN TITLE TEXT*/
	this->title = new sf::Text("FMQ Challenge!", *this->font, 128U);
	//centre the text
	this->title->setOrigin(this->title->getGlobalBounds().width / 2, this->title->getGlobalBounds().height / 2);
	//set the position
	this->title->setPosition(window->getSize().x / 2, window->getSize().y / 5);

	/*HOW To play TEXT*/
	this->rules1 = new sf::Text("1 Credit to play!\nWin credits: Number of balls in display", *this->font, 26U);
	//centre the text
	this->rules1->setOrigin(this->title->getGlobalBounds().width / 2, this->title->getGlobalBounds().height / 2);
	//set the position
	this->rules1->setPosition(window->getSize().x / 2, window->getSize().y / 1.25);


	/*HOW To play TEXT*/
	this->rules2 = new sf::Text("Use SPACE to Select Options// A: CREDITS IN // R: CREDITS OUT", *this->font, 26U);
	//centre the text
	this->rules2->setOrigin(this->title->getGlobalBounds().width / 2, this->title->getGlobalBounds().height / 2);
	//set the position
	this->rules2->setPosition(window->getSize().x / 2, window->getSize().y / 1.10);

	/*PLAY TEXT*/
	this->play = new sf::Text("Start!", *this->font, 32U);
	//centre the text
	this->play->setOrigin(this->play->getGlobalBounds().width / 2, this->play->getGlobalBounds().height / 2);
	//set the position
	this->play->setPosition(window->getSize().x / 2, window->getSize().y / 2);


	/*QUIT TEXT*/
	this->quit = new sf::Text("Quit!", *this->font, 32U);
	//centre the text
	this->quit->setOrigin(this->quit->getGlobalBounds().width / 2, this->quit->getGlobalBounds().height / 2);
	//set the position
	this->quit->setPosition(window->getSize().x / 2, window->getSize().y / 1.5);

	std::cout << "Initialised" << std::endl;
}


void main_menu::Render(sf::RenderWindow* window) {
	//create play and quit options
	this->play->setFillColor(sf::Color::White);
	this->quit->setFillColor(sf::Color::White);

	if (this->selected == 0) {
		this->play->setFillColor(sf::Color::Red);
	}
	else if (this->selected == 1) {
		this->quit->setFillColor(sf::Color::Red);
	}

	//draw the text on screen
	window->draw(*this->title);
	window->draw(*this->rules1);
	window->draw(*this->rules2);
	window->draw(*this->play);
	window->draw(*this->quit);
}


void main_menu::Update(sf::RenderWindow* window) {
	if (!this->upKey && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		this->selected -= 1;
	}
	if (!this->downKey && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		this->selected += 1;
	}
	//allow for cycling thorugh options...
	if (this->selected > 1) {
		this->selected = 0;
	}

	if (this->selected < 0) {
		this->selected = 1;
	}

	//Select the option using SPACE
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		switch (this->selected)
		{
		case 0:
			//play the game...
			core_state.SetState(new game());
			break;
		case 1:
			//quit the game...
			quitGame = true;
		default:
			break;
		}
	}


	//detect whether the up arrow has been pressed or not
	this->upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);

	//same for Down Key
	this->downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
}


void main_menu::Destroy(sf::RenderWindow* window) {
	delete this->font;
	delete this->title;
	delete this->play;
	delete this->quit;
	std::cout << "Destroyed" << std::endl;
}