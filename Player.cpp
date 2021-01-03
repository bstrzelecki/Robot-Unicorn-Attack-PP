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

	batch->DrawSurface(sprite, XPOSITION - 20, offset + SCREEN_HEIGHT/2);
}

void Player::ApplyMove(int delta)
{
	yPos += delta;
	height = yPos;

	bottomCollision = Point(XPOSITION, SCREEN_HEIGHT / 2 + 40 + offset);
	collisionThreshold = Point(XPOSITION, SCREEN_HEIGHT / 2 + 25 + offset);

	height = height > 0 ? height : 0;
	if (bottomCollision.y > SCENE_HEIGHT) {
		height = SCREEN_HEIGHT - bottomCollision.y + height;
	}
	offset = yPos - height;
}

void Player::Update(double delta) {
	if (isDashing) {
		currentDash += delta;
		moveBuffer = 0;
		if(currentDash > maxDashTime)
			isDashing = 0;
		return;
	}
	ApplyMove(moveBuffer * (delta + 1));
	if (isJumping == 1 || smallJump > 0) {
		if (currentJump < maxJump || smallJump > 0) {
			smallJump -= delta;
			currentJump += delta;
			// FIXME
			ApplyMove(-jumpRate*(1.0/currentJump)*(smallJump>0?1.25:1));
		}
		else {
			ApplyMove(.5 * gravity);
		}
		
	}
	else {
		ApplyMove(gravity);
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
