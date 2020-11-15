#pragma once
#include "entity.h"

class paddle_bullet : public Entity {
public:
	paddle_bullet(int bullet);
	void update();
private:
	int bulletNumber;
};