#include "Star.h"

Star::Star(Point start) : Platform(start, Point(STAR_WIDTH, STAR_HEIGHT))
{
	sprite = SDL_LoadBMP("./star.bmp");
}

void Star::Render(double delta, RenderBatch* batch)
{
	if (!isVisible)return;
	batch->DrawSurface(sprite, Position.x + Width/2, Position.y + Height/2);
}
