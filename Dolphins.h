#pragma once
#include "Prop.h"
class Dolphins : public Prop
{
public:
	Dolphins();
	~Dolphins();
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
	void Run(int count);
private:
	SDL_Surface* sprite;
	int offset = 300;
	int commonX = 0;
	int count = 0;
	int score;
};

