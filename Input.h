#pragma once

#include "./SDL2-2.0.10/include/SDL_events.h"
class Input
{
public:
	virtual void Resolve(SDL_Event e) abstract;
};

