#pragma once
#include "Collider.h"
#include "SDL2-2.0.10/include/SDL_surface.h"
#include "Prop.h"
#include <cstdio>
#include <cstdlib>
class Platform: public Prop
{
public:
	Platform(Point start, Point size);
	~Platform();
	int TestCollision(int playerY);
	void Reset();
	Point Position;
	Point startingPosition;
	int Width;
	int Height;
	void AddBonus(Platform* bonus);
	void AddStar(Platform* star);
	void Loop(int width);
	void Randomize();
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
	Platform** bonuses;
	Platform** stars;
	int isVisible = 1;
	int starCount = 0;
	int bonusCount = 0;
private:
	Collider* topCollider;
	Collider* bottomCollider;
};

