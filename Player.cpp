#include "Player.h"


Player::Player() {
	sprite = SDL_LoadBMP("./player.bmp");
	height = 0;
	
}
Player::~Player()
{
	SDL_FreeSurface(sprite);
}
void Player::Move(int deltaY)
{
	moveBuffer += deltaY;
}
void Player::Render(double delta, RenderBatch* batch) {
	batch->DrawPixel(bottomCollision.x, bottomCollision.y, 0xFF0000);
	batch->DrawPixel(collisionThreshold.x, collisionThreshold.y, 0xFF00FF);
	batch->DrawSurface(sprite, XPOSITION - 20, height);
}
void Player::Update(double delta) {
	if (isDashing) {
		currentDash += delta;
		moveBuffer = 0;
		if(currentDash > maxDashTime)
			isDashing = 0;
		return;
	}
	height += moveBuffer * (delta + 1);
	if (isJumping == 1 || smallJump > 0) {
		if (currentJump < maxJump || smallJump > 0) {
			smallJump -= delta;
			currentJump += jumpRate * (delta + 1);
			height -= jumpRate*(1.0/currentJump* (delta + 1));
		}
		else {
			height += .5 * gravity;
		}
		
	}
	else {
		height += gravity;
	}
	bottomCollision = Point(XPOSITION, height + 40);
	collisionThreshold = Point(XPOSITION, height + 25);
	height = height > 0 ? height : 0;
	if (bottomCollision.y > SCREEN_HEIGHT) {
		RestoreJumps();
		height = SCREEN_HEIGHT - bottomCollision.y + height;
	}
	moveBuffer = 0;
}

void Player::Jump()
{
	if (jumpCount > 0 && !isJumping) {
		smallJump = .25;
		isJumping = 1;
		currentJump = 1;
		jumpCount--;
	}
	
}

void Player::Dash()
{
	if (isDashing || !canDash)
		return;
	currentDash = 0;
	isDashing = 1;
	RestoreJumps(1);
	canDash = 0;
}

void Player::SetGravity(int gravity)
{
	this->gravity = gravity;
}

void Player::StopJump()
{
	isJumping = 0;
}

void Player::RestoreJumps(int count)
{
	jumpCount = count;
	canDash = 1;
}
