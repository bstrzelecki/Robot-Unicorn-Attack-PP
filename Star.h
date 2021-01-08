#pragma once
#include "Platform.h"
class Star :public Platform
{
public:
	Star(Point start);
	virtual void Render(double delta, RenderBatch* batch) override;
private:
	SDL_Surface* sprite;
};

