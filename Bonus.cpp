#include "Bonus.h"

Bonus::Bonus(Point start) : Platform(start, Point(30, 30))
{
	sprite = SDL_LoadBMP("./fairy.bmp");
}

void Bonus::Render(double delta, RenderBatch* batch)
{
	if (!isVisible)return;
	batch->DrawRectangle(Position.x, Position.y, Width, Height, 0xff0000, 0x00ff00);
	batch->DrawSurface(sprite, Position.x + 15, Position.y + 15);
}

