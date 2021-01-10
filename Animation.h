#pragma once
#include "SDL2-2.0.10/include/SDL_surface.h"
#include <cstdlib>
#include "statics.h"
#include <cstdio>
class Animation
{
public:
	// Input: 
	// name - name of folder containing animation (./)
	// count - number of  animation frames       
	Animation(char* name, int count);
	~Animation();
	// Output: return current animation frame
	SDL_Surface* GetCurrent();
	// Progresses throung animation depending of time passed
	// input delta - difference in miliseconds between frames
	void Advance(double delta);
	// Sets animation porgress to 0 shows first frame
	void Reset();
	// 1 - animation repeats istself
	// 0 - when completed animation stays at final frame
	int loop = 1;
	double duration = 1;
	double progress = 0;
private:
	int frameCount;
	SDL_Surface** frames;
};

