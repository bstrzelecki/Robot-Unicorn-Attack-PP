#pragma once
#include "Collider.h"
#include "SDL2-2.0.10/include/SDL_surface.h"
#include "Prop.h"
#include <cstdio>
class Platform: public Prop
{
public:
	Platform(Point start);
	~Platform();
	int TestCollision(int playerY);
	void Reset();
	Point Position;
	Point startingPosition;
	int Width;
	int Height;
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
private:
	SDL_Surface sprite;
	Collider* topCollider;
	Collider* bottomCollider;
};

