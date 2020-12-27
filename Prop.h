#pragma once
#include "RenderBatch.h"
class Prop
{
public:
	virtual void Render(double delta, RenderBatch* batch);
	virtual void Update(double delta);
};

