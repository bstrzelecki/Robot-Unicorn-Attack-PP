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
	batch->DrawSurface(sprite, XPOSITION, height);
}
void Player::Update(double delta) {
	height += moveBuffer * (delta + 1);
	height = height > 0 ? height : 0;
	height = height < SCREEN_HEIGHT? height: SCREEN_HEIGHT;
	moveBuffer = 0;
}