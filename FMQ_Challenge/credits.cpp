#include "credits.h"

credits::credits(sf::Font& font, unsigned int size) : sf::Text("Credits: 0", font, size) {
	this->currentCredits = 0;
	this->currentRound = 0;
	this->removedCredits = 0;
}

void credits::addCredits() {
	this->currentCredits +=1;
}

void credits::addround() {
	this->currentRound += 1;
}

void credits::creditsUsed() {
		this->currentCredits -= 1;
}

int credits::getCurrentCredits() {
	return this->currentCredits;
}

int credits::getCurrentRound() {
	return this->currentRound;
}

void credits::creditsOut() {
	if (0 < this->currentCredits) {
		this->currentCredits -= 1;
		this->removedCredits += 1;
	}
}

void credits::update() {
	this->setString( "Credits: " + std::to_string(this->currentCredits) + " Credits OUT: " + std::to_string(this->removedCredits) + " Round: " + std::to_string(this->currentRound) );
}