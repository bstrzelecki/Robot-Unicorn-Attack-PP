#include "Dolphins.h"

Dolphins::Dolphins()
{
	sprite = SDL_LoadBMP("./dolphin.bmp");
}

Dolphins::~Dolphins()
{
	SDL_FreeSurface(sprite);
}

void Dolphins::Render(double delta, RenderBatch* batch)
{
	for (int i = 0; i < count; i++) {
		// curve: y = 100sin(x/80)
		batch->DrawSurface(sprite, commonX - i * offset, 100 * SDL_sin(((double)commonX - i * (double)offset) / 80) + SCREEN_HEIGHT);
	}
}

void Dolphins::Update(double delta)
{
	commonX += delta + 1;
	if (commonX - count* offset > SCREEN_WIDTH * 2) {
		commonX = 0;
		count = 0;
	}
}

void Dolphins::Run(int count)
{
	this->count = count;
	commonX = 0;
}
