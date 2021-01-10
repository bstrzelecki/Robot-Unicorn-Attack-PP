#include "Star.h"

Star::Star(Point start) : Platform(start, Point(STAR_WIDTH, STAR_HEIGHT))
{
	sprite = SDL_LoadBMP("./star.bmp");
	destruction = new Animation("destruction", 15);
}

Star::~Star()
{
	delete destruction;
}

void Star::Render(double delta, RenderBatch* batch)
{
	if (!isVisible) {
		if(destruction->progress != 1 && destruction->progress != 0)
			batch->DrawSurface(destruction->GetCurrent(), Position.x + Width / 2, Position.y + Height / 2);
		return;
	}
	batch->DrawSurface(sprite, Position.x + Width/2, Position.y + Height/2);
}

void Star::Update(double delta)
{
	if (!isVisible) {
		destruction->Advance(delta);
	}
	else {
		destruction->Reset();
	}
}
