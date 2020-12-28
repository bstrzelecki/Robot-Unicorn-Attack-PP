#pragma once
#include "RenderBatch.h"
#define ABSTRACT =0
class Prop
{
public:
	virtual void Render(double delta, RenderBatch* batch) ABSTRACT;
	virtual void Update(double delta) ABSTRACT;
};

