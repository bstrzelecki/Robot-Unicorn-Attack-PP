#pragma once
#include <cstdio>
#include <cstring>
#include <cmath>
#include "Prop.h"
class ScoreBoard : public Prop
{
public:
	static void Save(char* name, int score);
	void Load();
	void Move(int delta);
	ScoreBoard();
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
private:
	void Sort();
	void Swap(int a, int b);
	int offset = 0;
	int count = 0;
	char names[BUFFSIZE][NAME_MAX_LENGHT];
	int scores[BUFFSIZE];
};

