#pragma once
#include "Prop.h"
#include <cstdio>
#include <cstring>
class FinalScore : public Prop
{
public:
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
	void AddChar(char* c);
	int score;
	char name[32];
};

