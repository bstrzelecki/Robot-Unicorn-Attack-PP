#include "Bonus.h"

Bonus::Bonus(Point start) : Platform(start, Point(BONUS_SIZE, BONUS_SIZE))
{
	sprite = SDL_LoadBMP("./fairy.bmp");
}

void Bonus::Render(double delta, RenderBatch* batch)
{
	if (!isVisible)return;
	batch->DrawSurface(sprite, Position.x + BONUS_SIZE /2, Position.y + BONUS_SIZE/2);
}

