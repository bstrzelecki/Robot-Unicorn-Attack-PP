#pragma once
#include "Collider.h"
#include <cmath>
class CurvedCollider : public Collider
{
public:
	CurvedCollider(int width, Direction direction, int startX,  double a, double b, double c);
	virtual int TestCollision(int playerY, Point platformPosition) override;
	int Polynomial(int x);
private:
	int startX;
	double a, b, c;
};

