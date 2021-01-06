#pragma once
#include "Prop.h"
#include "Platform.h"
#include <stdlib.h>
#include <cstdio>
#include "Player.h"
class Scene: public Prop
{
public:
	Scene(Player* player);
	~Scene();
	void Move(int delta);
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
	void TriggerDeath();
	int score=0;
	int scrollSpeed = 5;
private:
	int deathFlag = 0;

	int loopWidth;
	double speedUpTimer = 0;
	double speedUpMaxtime = 10;
	int maxScrollSpeed = 10;
	int platformCount = 0;
	Player* player;
	Platform** platforms;
};

