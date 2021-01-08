#include "Star.h"

Star::Star(Point start) : Platform(start, Point(115, 100))
{
	sprite = SDL_LoadBMP("./star.bmp");
}

void Star::Render(double delta, RenderBatch* batch)
{
	if (!isVisible)return;
	batch->DrawRectangle(Position.x, Position.y, Width, Height, 0xff0000, 0x00ff00);
	batch->DrawSurface(sprite, Position.x + Width/2, Position.y + Height/2);
}
