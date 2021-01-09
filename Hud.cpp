#include "Hud.h"

void Hud::Render(double delta, RenderBatch* batch)
{
	char buf[BUFFSIZE];
	sprintf(buf, "score: %d time: %ds", score, (int)(time));
	batch->DrawString(0, 0, buf);
	for (int i = 0; i < lives; i++) {
		batch->DrawSurface(liveSprite,2* LINE_SPACEING + i * 6 * LINE_SPACEING, LIVES_DISPLAY_Y);
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
