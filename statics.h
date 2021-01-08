#pragma once

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define SCENE_HEIGHT 1440
#define MAX_OFFSET 240

#define XPOSITION 85
#define ABSTRACT =0

#define NAME_MAX_LENGHT 28
#define BUFFSIZE 256

#define PAGE_SIZE 10

#define BONUS_POINTS 10
#define STAR_POINTS 100

enum class State{
	GameScreen,
	MenuScreen,
	DeathScreen,
	ScoreScreen
};

typedef enum {
	Up,
	Down
}Direction;

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