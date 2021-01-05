#pragma once
#include "Prop.h"
class FinalScore : public Prop
{
public:
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
};

