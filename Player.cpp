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
	bottomCollision = Point(XPOSITION, height + 40);
	collisionThreshold = Point(XPOSITION, height + 25);
	height = height > 0 ? height : 0;
	if (bottomCollision.y > SCREEN_HEIGHT) {
		height = SCREEN_HEIGHT - bottomCollision.y + height;
	}
	moveBuffer = 0;
}