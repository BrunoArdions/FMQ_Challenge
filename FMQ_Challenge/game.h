#pragma once

#include "game_state.h"
#include "main_menu.h"
#include "entity.h"
#include "paddle_bullet.h"
#include "ball.h"
#include "credits.h"

class game : public tiny_state {
public:
	void Initialize(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
	void addBall(sf::RenderWindow* window, credits* bullet1Score, int id);
	~game();
private:

	std::vector<ball*> vecBalls;
	std::vector<paddle_bullet*> vecbullets;
	paddle_bullet* bullet1;
	paddle_bullet* bullet2;
	paddle_bullet* bullet3;
	paddle_bullet* bullet4;
	ball* theBall;
	credits* bullet1Score;

	bool aKey, spaceKey, rKey;

	sf::Font* font;
};