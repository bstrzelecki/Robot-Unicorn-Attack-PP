#pragma once

#include "statics.h"

class Collider
{
public:
	Collider(int width, Direction direction);
	virtual int TestCollision(int playerY, Point platformPosition);
protected:
	int width;
	Direction direction;
};

