#pragma once
#include "Prop.h"
#include <cstdio>
#include <cstring>
class Hud : public Prop
{
public:
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
	Hud();
private:
	SDL_Surface* liveSprite;
	int lives = 3;
	int score = 0;
};

