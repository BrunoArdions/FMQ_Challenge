#pragma once

#include "paddle_bullet.h"
#include "credits.h"

class ball : public Entity {
public:
	ball( credits* creditBullet1, int id);
	void update(sf::RenderWindow* window, std::vector<ball*> vecBalls, std::vector<paddle_bullet*> vecbullets);
	void applyVelocity();
	bool bOut;
	bool bPoint;
	bool bstoped;
	void resetposition(sf::RenderWindow* window);
private:
	void collisionBalls(ball* b1, ball* b2);
	const sf::Color colorArray[5] = { sf::Color::Cyan, sf::Color::Blue, sf::Color::Green, sf::Color::Red, sf::Color::Yellow };
	
	credits* credit1;
	// Threshold indicating stability of object
	float fStable = 0.02f;
	int id;
};