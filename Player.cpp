#include "Player.h"

#define XPOSITION 65

Player::Player() {
	sprite = SDL_LoadBMP("./player.bmp");
	height = 0;
}
Player::~Player()
{
	SDL_FreeSurface(sprite);
}
void Player::Render(double delta, RenderBatch* batch) {
	batch->DrawSurface(sprite, XPOSITION, height);
}
void Player::Update(double delta) {

}