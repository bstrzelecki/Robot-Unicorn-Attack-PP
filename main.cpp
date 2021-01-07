#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
#include "RenderBatch.h"
#include "Player.h"


#include "statics.h"

// main
#ifdef __cplusplus

#endif
#include "Input.h"
#include "ArrowKeyController.h"
#include "Platform.h"
#include "Game.h"
int main(int argc, char **argv) {
	Game game;
	game.Run();
	return 0;
}