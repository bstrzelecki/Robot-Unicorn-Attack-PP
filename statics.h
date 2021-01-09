#pragma once

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define SCENE_HEIGHT 1440
#define MAX_OFFSET 240

#define XPOSITION 85
#define BASE_SCROLLSPEED 1
#define BASE_GRAVITY 2

#define NAME_MAX_LENGHT 28
#define BUFFSIZE 256

#define PAGE_SIZE 10
#define CHAR_WIDTH 8

#define BONUS_POINTS 10
#define STAR_POINTS 100
#define DOLPHIN_TRIGGER 10000

#define ABSOLUTE_MOVE_SPEED 10

#define BONUS_SIZE 30

#define STAR_WIDTH 115
#define STAR_HEIGHT 100

#define LINE_SPACEING 10

#define SPAWN_CHANCE_OFFSET 3

#define LIVES_DISPLAY_Y 25
#define STARTING_LIVES 3

#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff

#define DEFAULT_OFFSET 20
#define JUMP_ANIMATION_OFFSET 150
#define DASH_ANIMATION_OFFSET 100

#define COLLISION_OFFSET 40
#define COLLISION_THRESHOLD 25

#define MINUMUM_JUMP_DURATION .25

enum class State{
	GameScreen,
	MenuScreen,
	DeathScreen,
	ScoreScreen
};

enum class Direction {
	Up,
	Down
};

typedef enum {
	Jump,
	Fall,
	SlowFall
} JumpMode;



typedef struct Point{
	int x;
	int y;
	Point() {
		x = 0;
		y = 0;
	}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
}Point;