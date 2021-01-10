#pragma once
#include "Platform.h"
#include "Animation.h"
class Star :public Platform
{
public:
	Star(Point start);
	~Star();
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
private:
	Animation* destruction;
	SDL_Surface* sprite;
};

