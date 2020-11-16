#include "ball.h"
#include <iostream>

ball::ball( credits* creditBullet1,int id) {

	//find their scores
	this->bOut= false;
	this->bPoint = true;
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
	//// against other balls
	//for (auto &target : vecBalls)
	//{
	//	if (this->id != target->id) // do not check against self
	//	{
	//
	//			if (this-> checkCollision(target)) {
	//				collisionBalls(this, target);
	//			}
	//		}
	//	}

	//if it hits the ceiling
	if (this->getPosition().y < 0 || this->getPosition().y + this->getGlobalBounds().height > window->getSize().y) {
		this->velocity.y *= -1;
	}



	if (!(this->bstoped)) 
	{
		this->velocity.x -=  0.01f;					// Apply drag and gravity
		this->velocity.y -=  0.01f;


		// Stop ball when velocity is neglible
		if (this->velocity.x < fStable && this->velocity.y < fStable)
		{
			this->velocity.x = 0;
			this->velocity.y = 0;
			this->bstoped = true;
		}
	} 
	//see whether the players have scored a point
		if (this->getPosition().x < 5 && !bOut) {	
		this->bPoint=false;
		this->velocity.x = 0;
		this->velocity.y = 0;
	}

	if (this->getPosition().x > window->getSize().x - 5 && bOut) {
		this->bPoint = false;
		this->velocity.x = 0;
		this->velocity.y = 0;
	}
	Entity::update();
}

// Apply velocity
void ball::applyVelocity() 
{
	srand(time(NULL));
	// Apply velocity
	this->velocity.x = 3 +static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1)));;
	this->velocity.y = 3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1)));;
	this->bstoped = false;
	this->bOut = false;

}


void ball::collisionBalls(ball* b1, ball* b2) {
	float fEfficiency = 1.00f;
	float mass = 10.00f;
	// Distance between balls
	float fDistance = sqrtf((b1->getPosition().x - b2->getPosition().x)*(b1->getPosition().x - b2->getPosition().x) + (b1->getPosition().y - b2->getPosition().y)*(b1->getPosition().y - b2->getPosition().y));

	// Normal
	float nx = (b2->getPosition().x - b1->getPosition().x) / fDistance;
	float ny = (b2->getPosition().y - b1->getPosition().y) / fDistance;

	// Tangent
	float tx = -ny;
	float ty = nx;

	// Dot Product Tangent
	float dpTan1 = b1->velocity.x * tx + b1->velocity.y * ty;
	float dpTan2 = b2->velocity.x  * tx + b2->velocity.y * ty;

	// Dot Product Normal
	float dpNorm1 = b1->velocity.x  * nx + b1->velocity.y * ny;
	float dpNorm2 = b2->velocity.x  * nx + b2->velocity.y  * ny;

	// Conservation of momentum in 1D
	float m1 = fEfficiency * (dpNorm1 *  + 2.0f * mass * dpNorm2) / 20;
	float m2 = fEfficiency * (dpNorm2 *  + 2.0f * mass * dpNorm1) / 20;

	// Update ball velocities
	b1->velocity.x = tx * dpTan1 + nx * m1;
	b1->velocity.y = ty * dpTan1 + ny * m1;
	b2->velocity.x = tx * dpTan2 + nx * m2;
	b2->velocity.y = ty * dpTan2 + ny * m2;
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
	this->bstoped = false;
	std::cout << velocity.x << " " << velocity.y << std::endl;
}