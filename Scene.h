#pragma once
#include "Prop.h"
#include "Platform.h"
#include <stdlib.h>
#include <cstdio>
#include "Player.h"
#include "Bonus.h"
#include <cstring>
#include "Star.h"
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
	void AddBonusPoints();
	void AddStarPoints();
	int loopWidth;
	int bonusStreak = 1;
	int starStreak = 1;
	int displayedBonus = 0;
	double bonusTimer = 0;
	double bonusDuration = 1;
	double speedUpTimer = 0;
	double speedUpMaxtime = 10;
	int maxScrollSpeed = 10;
	int platformCount = 0;
	Player* player;
	Platform** platforms;
};

