#pragma once

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define XPOSITION 65
#define ABSTRACT =0

typedef enum {
	Up,
	Down
}Direction;

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