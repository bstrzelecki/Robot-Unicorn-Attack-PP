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
	int score = 0;
	int lives = 3;
private:
	SDL_Surface* liveSprite;
	double time = 0;
};

