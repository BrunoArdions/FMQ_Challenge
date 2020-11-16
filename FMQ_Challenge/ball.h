#pragma once

#include "paddle_bullet.h"
#include "credits.h"

class ball : public Entity {
public:
	ball( credits* creditBullet1, int id);
	void update(sf::RenderWindow* window, std::vector<ball*> vecBalls, std::vector<paddle_bullet*> vecbullets);
	void applyVelocity();
	bool bOut;
	bool bstoped;
private:
	const sf::Color colorArray[5] = { sf::Color::Cyan, sf::Color::Blue, sf::Color::Green, sf::Color::Red, sf::Color::Yellow };
	void resetposition(sf::RenderWindow* window);
	credits* credit1;
	// Threshold indicating stability of object
	float fStable = 0.05f;
	int id;
};