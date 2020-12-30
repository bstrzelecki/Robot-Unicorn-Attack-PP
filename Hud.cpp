#include "Hud.h"

void Hud::Render(double delta, RenderBatch* batch)
{
	char buf[256];
	sprintf(buf, "score: %d", score);
	batch->DrawString(0, 0, buf);
	for (int i = 0; i < lives; i++) {
		batch->DrawSurface(liveSprite,20 + i * 60, 20);
	}
}

void Hud::Update(double delta)
{
}

Hud::Hud()
{
	liveSprite = SDL_LoadBMP("./live.bmp");

}
