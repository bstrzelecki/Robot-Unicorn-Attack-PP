#include "Animation.h"

Animation::Animation(char* name, int count)
{
	frames = new SDL_Surface*[count];
	if (frames== nullptr) {
		frameCount = 0;
		return;
	}
	else {
		frameCount = count - 1;
	}
	for (int i = 1; i <= count; i++) {
		char strBuff[BUFFSIZE] = "";
		sprintf(strBuff, "./%s/%d.bmp", name, i);
		frames[i-1] = SDL_LoadBMP(strBuff);
	}
}

Animation::~Animation()
{
	for (int i = 0; i < frameCount; i++) {
		SDL_FreeSurface(frames[i]);
	}
}

SDL_Surface* Animation::GetCurrent()
{
	double p = progress / duration * frameCount;
	p += 0.5 - (p < 0);
	int x = (int)p;
	return frames[x];
}

void Animation::Advance(double delta)
{
	progress += delta;
	if (progress > duration) {
		if (loop) {
			progress = 0;
		}
		else {
			progress = duration;
		}
	}
}

void Animation::Reset()
{
	progress = 0;
}
