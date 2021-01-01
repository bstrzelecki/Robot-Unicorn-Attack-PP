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
	void Dash();
	void SetGravity(int gracvity);
	void StopJump();
	void RestoreJumps(int count = 2);
	int height;
	int isDashing = 0;
	Point topCollision, bottomCollision, collisionThreshold;
private:
	int isJumping=0;
	int jumpRate = 2;
	int canDash = 1;
	double currentDash = 0;
	double smallJump = 0;
	double maxDashTime = .4;
	double currentJump = 1;
	double maxJump = 450;
	int gravity = 2;
	int jumpCount = 2;
	SDL_Surface* sprite;
	int moveBuffer = 0;
};

