#include "Hud.h"

void Hud::Render(double delta, RenderBatch* batch)
{
	char buf[256];
	sprintf(buf, "score: %d time: %ds", score, (int)(time));
	batch->DrawString(0, 0, buf);
	for (int i = 0; i < lives; i++) {
		batch->DrawSurface(liveSprite,20 + i * 60, 25);
	}
}

void Hud::Update(double delta)
{
	time += delta;
}

Hud::Hud()
{
	liveSprite = SDL_LoadBMP("./live.bmp");

}
