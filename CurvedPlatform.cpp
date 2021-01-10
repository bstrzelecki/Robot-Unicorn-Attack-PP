#include "CurvedPlatform.h"

CurvedPlatform::CurvedPlatform(Point start, Point size, double a, double b, double c) : Platform(start, size) {
	this -> a = a;
	this -> b = b;
	this -> c = c;

	topCollider = new CurvedCollider(Width, Direction::Up, start.x,  a, b, c);
	bottomCollider = new CurvedCollider(Width, Direction::Down,start.x, a, b, c);
}

void CurvedPlatform::Render(double delta, RenderBatch* batch)
{
	for (int i = 0; i < Width; i++) {
		batch->DrawLine(Position.x + i, Position.y + Polynomial(i) , Height, 0, 1, RED);
	}
}

int CurvedPlatform::GetY()
{
	return Position.y + Polynomial(XPOSITION - Position.x);
}

int CurvedPlatform::Polynomial(int x)
{
	double scale = (double)x / Width;
	return (a * pow(scale, 3) + b * pow(scale, 2) + c * scale) * 100;
}
