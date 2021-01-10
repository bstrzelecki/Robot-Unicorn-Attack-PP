#pragma once
#include "Collider.h"
#include "SDL2-2.0.10/include/SDL_surface.h"
#include "Prop.h"
#include <cstdio>
#include <cstdlib>
class Platform: public Prop
{
public:
	// Default rectangular platform type
	Platform(Point start, Point size);
	~Platform();
	// 1 - if point collides with platform
	// 0 - if not
	int TestCollision(int playerY);
	Point Position;
	Point startingPosition;
	int Width;
	int Height;
	// Adds pickable bonus
	void AddBonus(Platform* bonus);
	// Adds stars that player needs to dash throught 
	void AddStar(Platform* star);
	void Loop(int width);
	void Randomize();
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
	void SetBuffers(int bonus, int star);
	virtual int GetY();
	Platform** bonuses;
	Platform** stars;
	int isVisible = 1;
	int starCount = 0;
	int bonusCount = 0;
	int randomOffset = 0;
private:
	void UpdatePickup(Platform** list, int count);
	void ResetPickups(Platform** list, int count);
	void DrawPickup(Platform** list, int count, double delta, RenderBatch* batch);
protected:
	Collider* topCollider;
	Collider* bottomCollider;
};

