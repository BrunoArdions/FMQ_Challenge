#include "ball.h"
#include <iostream>

ball::ball( credits* creditBullet1,int id) {

	//find their scores
	this->bOut= false;
	this->bstoped = true;
	this->credit1 = creditBullet1;
	this->Load("ball.png");
	this->setScale(0.7f, 0.7f);
	this->id = id;
	this->velocity.x = 1;
	this->velocity.y = 1;
}


void ball::update(sf::RenderWindow* window, std::vector<ball*> vecBalls, std::vector<paddle_bullet*> vecbullets) {
	


	for (auto &bullet : vecbullets)
	{
		//check whether the ball has hit a bullet or not.
		if (this->checkCollision(bullet)) {
			this->velocity.x *= -1;
		}
	}
	// against other balls
	for (auto &target : vecBalls)
	{
		if (this->id != target->id) // do not check against self
		{
	
				if (this-> checkCollision(target)) {
					this->velocity.x *= -1;
					this->velocity.y *= -1;
				}
			}
		}

	//if it hits the ceiling
	if (this->getPosition().y < 0 || this->getPosition().y + this->getGlobalBounds().height > window->getSize().y) {
		this->velocity.y *= -1;
	}
	if (!(this->bstoped))
	{
		this->velocity.x -= this->velocity.x * 0.99f;					// Apply drag and gravity
		this->velocity.y -= this->velocity.y * 0.99f;
		// Stop ball when velocity is neglible
		if (fabs(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y) < fStable)
		{

			this->velocity.x = 0;
			this->velocity.y = 0;
			this->bstoped = true;
		}
	} 
	//see whether the players have scored a point
		if (this->getPosition().x < 5 && !bOut) {	
		this->bOut=true;
	}

	if (this->getPosition().x > window->getSize().x - 5 && bOut) {
		this->bOut = true;
	}
	Entity::update();
}

// Apply velocity
void ball::applyVelocity() 
{
	srand(time(NULL));
	// Apply velocity
	this->velocity.x = 1 +static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1)));;
	this->velocity.y = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1)));;
	this->bstoped = false;

}

// restart balls
void ball::resetposition(sf::RenderWindow* window) {
	//seed the random number generator
	srand(time(NULL));
	this->setPosition(((float)rand() / (float)RAND_MAX) * window->getSize().x, ((float)rand() / (float)RAND_MAX) * window->getSize().y);
	velocity.x = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1)));
	if (rand() % 2 == 0) {
		velocity.x *= -1;
	}
	velocity.y = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1)));
	if (rand() % 2 == 0) {
		velocity.y *= -1;
	}
	std::cout << velocity.x << " " << velocity.y << std::endl;

}