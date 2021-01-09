#include "Collider.h"
Collider::Collider(int width, Direction direction)
{
    this->width = width;
    this->direction = direction;
}
int Collider::TestCollision(int playerY, Point platformPosition)
{
	if (XPOSITION < platformPosition.x || XPOSITION > platformPosition.x + width)
		return 0;
	switch (direction)
	{
		case Direction::Up:
			return playerY > platformPosition.y;
		case Direction::Down:
			return playerY < platformPosition.y;
	}
    return 0;
}
