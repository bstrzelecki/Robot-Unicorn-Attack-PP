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
	height += moveBuffer * (delta + 1);
	if (isJumping == 1) {
		if (currentJump < maxJump) {
			currentJump += jumpRate * (delta + 1);
			height -= jumpRate*(1.0/currentJump* (delta + 1));
		}
		else {
			height += .5 * gravity;
		}
		
	}
	if (isJumping == 0)
		height += gravity;
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
	if (jumpCount > 0) {
		isJumping = 1;
		jumpTime = 1;
		jumpCount--;
	}
	
}

void Player::StopJump()
{
	currentJump = 0;
	isJumping = 0;
}

void Player::RestoreJumps(int count)
{
	jumpCount = count;
}
