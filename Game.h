#pragma once
#include "Scene.h"
#include "Player.h"
#include "Input.h"
#include "ArrowKeyController.h"
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
#include "Hud.h"
#include "ZXController.h"
#include "Menu.h"
#include "Death.h"
#include "FinalScore.h"
#include "Scoreboard.h"
#include <time.h>
#include "Dolphins.h"
#include "statics.h"


typedef struct {
	int* quit;
	int* restartFlag;
	double delta;
	RenderBatch* batch;
}GameDescriptor;

class Game
{
public:
	Game();
	~Game();
	void Run();
	void ScoreLoop(GameDescriptor game);
	void DeathLoop(GameDescriptor game);
	void MenuLoop(GameDescriptor game);
	void GameLoop(Input* defaultInput, Input* arrowInput, int* ddl, Dolphins* dolphins, GameDescriptor game);
	void SetState(State state);
	void Init();
	void Dispose();
private:
	int totalScore = 0;
	char name[32]="";
	int nameLenght = 0;
	int lives=3;
	Menu* menu;
	Death* death;
	ScoreBoard scoreboard;
	FinalScore* finalScore;
	State currentState = State::MenuScreen;
	Scene* scene;
	Player* player;
	Input* input;
	Hud* hud;
	SDL_Surface* screen, * charset;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

