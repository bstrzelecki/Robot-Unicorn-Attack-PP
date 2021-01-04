#include "Platform.h"

Platform::Platform(Point start)
{
	Position = start;
	Width = 600;
	Height = 40;
	startingPosition = start;
	topCollider = new Collider(Width, Up);
	bottomCollider = new Collider(Width, Down);
}

Platform::~Platform()
{
	delete topCollider;
	delete bottomCollider;
}

int Platform::TestCollision(int playerY)
{
	if (topCollider->TestCollision(playerY, Position) &&
		bottomCollider->TestCollision(playerY, Point(Position.x, Position.y + Height)))
		return 1;
	else
		return 0;
}

void Platform::Reset()
{
	Position = startingPosition;
}

void Platform::Render(double delta, RenderBatch* batch)
{
	batch->DrawRectangle(Position.x, Position.y, Width, 40, 0xff0000, 0x00ff00);
}

void Platform::Update(double delta)
{
}
