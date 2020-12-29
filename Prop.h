#pragma once
#include "RenderBatch.h"
#include "statics.h"
class Prop
{
public:
	virtual void Render(double delta, RenderBatch* batch) abstract;
	virtual void Update(double delta) abstract;
};

