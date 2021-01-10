#include "CurvedCollider.h"

CurvedCollider::CurvedCollider(int width, Direction direction,int startX, double a, double b, double c):Collider(width, direction)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->startX = startX;
}

int CurvedCollider::TestCollision(int playerY, Point platformPosition)
{
	if (XPOSITION < platformPosition.x || XPOSITION > platformPosition.x + width)
		return 0;
	switch (direction)
	{
	case Direction::Up:
		return playerY > platformPosition.y + Polynomial(XPOSITION - platformPosition.x);
	case Direction::Down:
		return playerY < platformPosition.y + Polynomial(XPOSITION - platformPosition.x);
	}
	return 0;
}
int CurvedCollider::Polynomial(int x)
{
	double scale = (double)x / width;
	return (a * pow(scale, 3) + b * pow(scale, 2) + c * scale) * 100;
}