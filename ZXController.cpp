#include "ZXController.h"

ZXController::ZXController(Player* player)
{
	this->player = player;
}

void ZXController::Resolve(SDL_Event e)
{
	switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
				case SDLK_z:
					player->Jump();
					break;
				case SDLK_x:
					player->Dash();
					break;
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
			case SDLK_z:
				player->StopJump();
				break;
			}
			break;


	}
}
