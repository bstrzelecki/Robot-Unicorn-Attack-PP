#pragma once
#include "Input.h"
#include "Player.h"
class ZXController : public Input
{
public:
	// Default controler
	// Z - jump
	// X - dash
	ZXController(Player* player);
	virtual void Resolve(SDL_Event e) override;
private:
	Player* player;
};

