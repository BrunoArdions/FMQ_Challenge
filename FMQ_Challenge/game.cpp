#include "game.h"
#include "main_menu.h"
#include "ball.h"
#include <iostream>
#include "game_state.h"

sf::Event event;
bool pauseGame = true;
bool playing = false;
int countballStoped = 0;


void game::Initialize(sf::RenderWindow* window) {
	//initialise the font
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/gamefont.ttf");

	//initialise the score texts
	this->bullet1Score = new credits(*font, 32U);

	this->bullet1 = new paddle_bullet();
	this->bullet1->setPosition(30, window->getSize().y / 4);
	this->bullet3 = new paddle_bullet();
	this->bullet3->setPosition(30, window->getSize().y * 3 / 4);
	
	/*PAUSE TEXT*/
	this->pauseText= new sf::Text("Game Paused!", *this->font, 32U);

	this->pauseText->setOrigin(this->pauseText->getGlobalBounds().width / 2, this->pauseText->getGlobalBounds().height / 2);
	//set the position
	this->pauseText->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	/*Round TEXT*/
	this->roundText = new sf::Text("Round Ended!", *this->font, 32U);

	this->roundText->setOrigin(this->roundText->getGlobalBounds().width / 2, this->roundText->getGlobalBounds().height / 2);
	//set the position
	this->roundText->setPosition(window->getSize().x / 2, window->getSize().y / 2);

	this->bullet2 = new paddle_bullet();;
	//move bullet2 to the right
	this->bullet2->setPosition(window->getSize().x - this->bullet2->getGlobalBounds().width - 30, window->getSize().y /  4);
	this->bullet4 = new paddle_bullet();
	this->bullet4->setPosition(window->getSize().x - this->bullet4->getGlobalBounds().width - 30, window->getSize().y *3 / 4);

	vecbullets.emplace_back(bullet1);
	vecbullets.emplace_back(bullet2);
	vecbullets.emplace_back(bullet3);
	vecbullets.emplace_back(bullet4);
	
	for (int i = 0; i < 50; i++) {
		addBall(window, bullet1Score, vecBalls.size());
	}
}


void game::addBall(sf::RenderWindow* window, credits* bullet1Score, int id) {
	ball* b = new ball(bullet1Score, id);
	vecBalls.emplace_back(b);
	b->setPosition(((float)rand() / (float)RAND_MAX) * window->getSize().x, ((float)rand() / (float)RAND_MAX) * window->getSize().y);
}

void game::Render(sf::RenderWindow* window) {
	window->draw(*this->bullet1Score);
	for (auto &ball : vecBalls) {
		window->draw(*ball);
	}

	window->draw(*this->bullet1);
	window->draw(*this->bullet2);
	window->draw(*this->bullet3);
	window->draw(*this->bullet4);
}


void game::Update(sf::RenderWindow* window) {
	
		
		if(pauseGame && playing && 0 < bullet1Score->getCurrentRound()) {
		window->draw(*this->pauseText);
		}
		else if (pauseGame && !playing && 0 < bullet1Score->getCurrentRound()) {
			window->draw(*this->roundText);
		}
		//condition to pause the game
		if (!this->spaceKey && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && playing) {
			
			pauseGame = !pauseGame;
		}

		//condition to start the game
		if (!this->spaceKey && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (!playing) && 0 < this->bullet1Score->getCurrentCredits()) {
			playing = true;
			this->bullet1Score->creditsUsed();
			pauseGame = false;
			this->bullet1Score->addround();
			for (auto &ball : vecBalls)
			{
				ball->applyVelocity();
			}
		}

		//condition to add credits
		if (!this->aKey && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			this->bullet1Score->addCredits();
		}

		//condition to remove credits
		if (!this->rKey && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
			this->bullet1Score->creditsOut();
		}

		this->bullet1Score->update();
		
		if (!pauseGame)
		{	
			// delete pause text
			//TODO second game mode to be finished 
			//this->bullet1->update();
			//this->bullet2->update();
			for (auto &ball : vecBalls) {
				ball->update(window, vecBalls, vecbullets);
				if (ball->bstoped && !(ball->bOut)) {
					countballStoped++;
					ball->bOut = true;	
				}
			}
			//end round TODO clear magic balls number
			if (50 == countballStoped && playing) {
				pauseGame = true;
				playing = false;
				countballStoped = 0;
				for (auto &ball : vecBalls) {
					if (ball->bPoint)
						this->bullet1Score->addCredits();
				}

				
				
	
			}
		}

		// condition to return to the main menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			core_state.SetState(new main_menu());
		}

		//detect whether the A keyhas been pressed or not
		this->aKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);

		//same for space Key
		this->spaceKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

		//same for R Key
		this->rKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R);
}

void game::Destroy(sf::RenderWindow* window) {
	delete this->bullet1;   
	delete this->bullet2;
	delete this->bullet3;
	delete this->bullet4;
	for (auto ball : vecBalls)
		delete ball;
	delete this->bullet1Score;
}