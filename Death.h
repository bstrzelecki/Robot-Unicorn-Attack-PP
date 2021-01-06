#pragma once
#include "Prop.h"
#include <cstdio>
class Death : public Prop
{
public:
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
	int score = 0;
	int lives = 3;
};

