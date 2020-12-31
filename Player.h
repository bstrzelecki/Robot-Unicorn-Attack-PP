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
	void Jump();
	void StopJump();
	void RestoreJumps(int count = 2);
	int height;
	Point topCollision, bottomCollision, collisionThreshold;
private:
	int isJumping=0;
	int jumpTime = 0;
	int jumpRate = 2;
	double currentJump = 0;
	double maxJump = 450;
	int gravity = 2;
	int jumpCount = 2;
	SDL_Surface* sprite;
	int jumpVelocity;
	int moveBuffer = 0;
};

