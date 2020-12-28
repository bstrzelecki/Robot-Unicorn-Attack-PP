#pragma once
#include "Prop.h"
class Player : public Prop
{
public:
	Player();
	~Player();
	void Render(double delta, RenderBatch* batch);
	void Update(double delta);
private:
	SDL_Surface* sprite;
	int height;
};

