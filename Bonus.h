#pragma once
#include "Platform.h"
class Bonus : public Platform
{
public:
	Bonus(Point start);
	virtual void Render(double delta, RenderBatch* batch) override;
private:
	SDL_Surface* sprite;
};

