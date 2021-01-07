#pragma once
#include "SDL2-2.0.10/include/SDL_surface.h"
#include <cstdlib>
#include "statics.h"
#include <cstdio>
class Animation
{
public:
	Animation(char* name, int count);
	~Animation();
	SDL_Surface* GetCurrent();
	void Advance(double delta);
	void Reset();
	int loop = 1;
	double duration = 1;
private:
	int frameCount;
	SDL_Surface** frames;
	double progress = 0;
};

