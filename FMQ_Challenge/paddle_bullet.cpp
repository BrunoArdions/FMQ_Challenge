#include "paddle_bullet.h"

paddle_bullet::paddle_bullet() {
	
	
		this->Load("player1.png");
		this->setScale(2.5f, 2.5f);
	
}

void paddle_bullet::update() {


		//TODO make a second game mode similar to pong were paddles move up and down
		//this->velocity.y = 1
	
		////make sure the paddle calls the superclass' update to make things move
		//Entity::update();


		////make sure the paddles can't go off screen
		//if (this->getPosition().y < 0) {
		//	this->move(0, 1);

		//}
		//// 
		//if (this->getPosition().y + this->getGlobalBounds().height > 600) {
		//	this->move(0, -1);

		//}
};