#pragma once
#include "Scene.h"
#include "Player.h"
#include "Input.h"
#include "ArrowKeyController.h"
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
class Game
{
public:
	Game();
	~Game();
	void Run();
private:
	Scene* scene;
	Player* player;
	Input* input;
	SDL_Surface* screen, * charset;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

