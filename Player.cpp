#include "Player.h"


Player::Player() {
	sprite = SDL_LoadBMP("./player.bmp");
	run = new Animation("unicorn", 37);
	jump = new Animation("jump", 11);
	dash = new Animation("dash", 10);
	death = new Animation("death", 16);
	fall = new Animation("fall", 10);
	dash->duration = maxDashTime;
	death->duration = deathAnimationDuration;
	fall->loop = 0;
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
	batch->DrawPixel(bottomCollisionThreshold.x, bottomCollisionThreshold.y, 0xFF00FF);
	batch->DrawPixel(topCollision.x, topCollision.y, 0xFF0000);
	batch->DrawPixel(topCollisionThreshold.x, topCollisionThreshold.y, 0xFFFF00);

	int xOffset = 0;
	SDL_Surface* sp = run->GetCurrent();
	if (isFalling) {
		sp = fall->GetCurrent();
		xOffset = 150;
	}
	if (isJumping && currentJump < maxJump) {
		sp = jump->GetCurrent();
		xOffset = 150;
	}
	if (isDashing) {
		sp = dash->GetCurrent();
		xOffset = 100;
	}
	if (deathFlag) {
		sp = death->GetCurrent();
		xOffset = 0;
	}

	batch->DrawSurface(sp, XPOSITION - 20 - xOffset, offset + SCREEN_HEIGHT/2);
}

void Player::ApplyMove(int delta)
{
	yPos += delta;
	height = yPos;

	topCollision = Point(XPOSITION, SCREEN_HEIGHT / 2 - 40 + offset);
	topCollisionThreshold = Point(XPOSITION, SCREEN_HEIGHT / 2 - 25 + offset);

	bottomCollision = Point(XPOSITION, SCREEN_HEIGHT / 2 + 40 + offset);
	bottomCollisionThreshold = Point(XPOSITION, SCREEN_HEIGHT / 2 + 25 + offset);

	height = height > 0 ? height : 0;
	if (height > SCENE_HEIGHT) {
		height = SCENE_HEIGHT;
	}
	offset = yPos - height;
}

void Player::Kill()
{
	death->Reset();
	deathFlag = 1;
	deathAnimationTime = 0;
}

void Player::Update(double delta) {
	if (deathFlag) {
		deathAnimationTime += delta;
		death->Advance(delta);
		if (deathAnimationTime >= deathAnimationDuration) {
			isDead = 1;
		} 
		return;
	}
	if (isDashing) {
		currentDash += delta;
		dash->Advance(delta);
		moveBuffer = 0;
		if(currentDash > maxDashTime)
			isDashing = 0;
		return;
	}
	if (isFalling) {
		fall->Advance(delta);
	}
	else {
		fall->Reset();
	}
	run->Advance(delta);
	ApplyMove(moveBuffer * (delta + 1));
	if (isJumping == 1 || smallJump > 0) {
		if (currentJump < maxJump || smallJump > 0) {
			smallJump -= delta;
			currentJump += delta;
			jump->Advance(delta);
			ApplyMove(-jumpRate*(1.0/currentJump)*(smallJump>0?1.25:1));
		}
		else {
			ApplyMove(.5 * gravity);
		}
	}
	else {
		jump->Reset();
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
	if (isDashing || !canDash || dashKey)
		return;
	dash->Reset();
	currentDash = 0;
	dashKey = 1;
	isDashing = 1;
	RestoreJumps(1);
	canDash = 0;
}

void Player::StopDash()
{
	dashKey = 0;
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
