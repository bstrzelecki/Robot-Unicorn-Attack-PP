#include "Game.h"


Game::Game()
{
	Init();
}

Game::~Game()
{
	Dispose();
}

void Game::Run()
{


	double t1, t2, delta;
	t1 = SDL_GetTicks();
	int quit = 0;
	int restartFlag = 0;

	
	player = new Player();
	scene = new Scene(player);
	
	Input* arrowInput = new ArrowKeyController(player, scene);
	Input* defaultInput = new ZXController(player);



	input = defaultInput;
	int currentInput = 0;

	RenderBatch batch(screen, charset);
	while (!quit) {
		t2 = SDL_GetTicks();

		delta = (t2 - t1) * 0.001;
		t1 = t2;

		// background
		SDL_FillRect(screen, NULL, 0x000000);

		SDL_Event event;

		hud->score = scene->score;
		
		if (currentState == State::GameScreen) {
			while (SDL_PollEvent(&event)) {
				input->Resolve(event);
				switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = 1;
						break;
					case SDLK_n:
						quit = 1;
						restartFlag = 1;
						SetState(State::MenuScreen);
						break;
					case SDLK_d:
						if (input == defaultInput) {
							input = arrowInput;
							player->SetGravity(0);
							scene->scrollSpeed = 0;
						}
						else {
							input = defaultInput;
							player->SetGravity(2);
							scene->scrollSpeed = 1;
						}
					}
					break;
				}
			}

			player->Update(delta);
			scene->Update(delta);
			hud->Update(delta);

			scene->Render(delta, &batch);
			player->Render(delta, &batch);
			hud->Render(delta, &batch);

			if (player->isDead) {
				SetState(State::DeathScreen);
			}
		}

		if (currentState == State::MenuScreen) {
			while (SDL_PollEvent(&event)) {
				input->Resolve(event);
				switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							quit = 1;
							break;
						case SDLK_n:
							quit = 1;
							restartFlag = 1;
							SetState(State::GameScreen);
							break;
					}
					break;
				}
			}
			menu->Render(delta, &batch);
		}


		if (currentState == State::DeathScreen) {
			while (SDL_PollEvent(&event)) {
				input->Resolve(event);
				switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							quit = 1;
							break;
						case SDLK_c:
							quit = 1;
							restartFlag = 1;
							SetState(State::GameScreen);
							break;
						case SDLK_m:
							quit = 1;
							restartFlag = 1;
							SetState(State::MenuScreen);
							break;
					}
					break;
				}
			}
			death->Render(delta, &batch);
		}

		if (currentState == State::ScoreScreen) {
			while (SDL_PollEvent(&event)) {
				input->Resolve(event);
				switch (event.type) {
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							quit = 1;
							break;
						case SDLK_COMMA:
							quit = 1;
							restartFlag = 1;
							SetState(State::MenuScreen);
							break;
						}
						break;
					case SDL_TEXTINPUT:
						// Add backspace support
						if (nameLenght > 28)
							break;
						nameLenght++;
						strcat(name, event.text.text);
						strcpy(finalScore->name, name);
						break;
				}
			}
			finalScore->Render(delta, &batch);
		}


		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	if (restartFlag == 1) {
		delete player;
		delete scene;
		delete input;
		Run();
	}
}

void Game::SetState(State state)
{
	switch (state) {
		case State::GameScreen:
			hud->lives = lives;
			break;
		case State::MenuScreen:
			lives = 3;
			break;
		case State::DeathScreen:
			lives--;
			death->score = scene->score;
			totalScore += scene->score;
			death->lives = lives;
			if (lives == 0)
			{
				SetState(State::ScoreScreen);
				return;
			}
			break;
		case State::ScoreScreen:
			finalScore->score = totalScore;
			break;
	}
	currentState = state;
}


void Game::Init()
{
	int rc;

	menu = new Menu();
	death = new Death();
	finalScore = new FinalScore();
	hud = new Hud();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return;
	}

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "POP202_2");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return;
	}
	SDL_SetColorKey(charset, true, 0x000000);


}
void Game::Dispose()
{
	delete player;
	delete scene;
	delete input;
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}
