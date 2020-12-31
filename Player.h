#pragma once
#include "Prop.h"
#include "statics.h"
#include <cstdio>
class Player : public Prop
{
public:
	Player();
	~Player();
	void Move(int deltaY);
	void Render(double delta, RenderBatch* batch) override;
	void Update(double delta) override;
	int height;
	Point topCollision, bottomCollision, collisionThreshold;
private:
	SDL_Surface* sprite;
	int moveBuffer = 0;
};

