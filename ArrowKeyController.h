#pragma once
#include "Scene.h"
#include "Player.h"
#include "Input.h"
#include "./SDL2-2.0.10/include/SDL_events.h"
class ArrowKeyController: public Input
{
public:
	// Arrow key controlls
	ArrowKeyController(Player* player, Scene* scene);
	virtual void Resolve(SDL_Event e) override;
private:
	Player* player;
	Scene* scene;

};

