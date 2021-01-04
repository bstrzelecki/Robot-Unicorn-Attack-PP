#pragma once

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define SCENE_HEIGHT 1440
#define MAX_OFFSET 240

#define XPOSITION 85
#define ABSTRACT =0

typedef enum {
	GameMode,
	Menu,
	Death,
	Score
}State;

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