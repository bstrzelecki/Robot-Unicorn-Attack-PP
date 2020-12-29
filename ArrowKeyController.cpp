#include "ArrowKeyController.h"

ArrowKeyController::ArrowKeyController(Player* player, Scene* scene)
{
	this->player = player;
	this->scene = scene;
}

void ArrowKeyController::Resolve(SDL_Event e)
{
	switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					player->Move(-10);
					break;
				case SDLK_DOWN:
					player->Move(10);
					break;
				case SDLK_LEFT:
					scene->Move(-10);
					break;
				case SDLK_RIGHT:
					scene->Move(10);
					break;
			}
			break;
			
	}
}
