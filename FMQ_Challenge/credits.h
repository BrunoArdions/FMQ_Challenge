#pragma once

#include <SFML/Graphics.hpp>

//deal with keeping track of and displaying the credits and rounds of the game
class credits : public sf::Text {
public:
	credits(sf::Font& font, unsigned int size);
	void addCredits();
	void update();
	void addround();
	void creditsOut();
	void creditsUsed();
	int getCurrentCredits();

private:
	int currentCredits;
	int currentRound;
	int removedCredits;
};