#pragma once
#include "Prop.h"
#include "statics.h"
#include <cstdio>
#include "Animation.h"
class Player : public Prop
{
public:
	Player();
	~Player();
	// Move up and down
	void Move(int deltaY);
	void Render(double delta, RenderBatch* batch) override;
	void Update(double delta) override;
	void Jump();
	void StopJump();
	void Dash();
	void StopDash();
	void SetGravity(int gracvity);
	void Kill();
	void RestoreJumps(int count = 2);
	void ApplyMove(int delta);
	int height;
	int isDashing = 0;
	Point topCollision, bottomCollision, bottomCollisionThreshold, topCollisionThreshold;
	int offset = 0;
	int isDead = 0;
	int isFalling = 0;
private:
	int lastPos = 0;
	Animation* run;
	Animation* jump;
	Animation* dash;
	Animation* death;
	Animation* fall;
	double deathAnimationDuration = 1;
	double deathAnimationTime = 0;
	int deathFlag = 0;
	int yPos = 0;
	int dashKey = 0;
	int isJumping=0;
	int canDash = 1;
	double currentDash = 0;
	double currentJump = 1;
	double smallJump = 0;
	// Dash settings
	double maxDashTime = .4;
	// Jump settings
	int jumpRate = 2;
	double maxJump = 2;
	int jumpCount = 2;
	int gravity = 2;

	SDL_Surface* sprite;
	int moveBuffer = 0;
};

