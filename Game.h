#pragma once
#include "Scene.h"
#include "Player.h"
#include "Input.h"
#include "ArrowKeyController.h"
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
#include "Hud.h"
#include "ZXController.h"

class Game
{
public:
	Game();
	~Game();
	void Run();
	void Init();
	void Dispose();
private:
	Scene* scene;
	Player* player;
	Input* input;
	Hud* hud;
	SDL_Surface* screen, * charset;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

