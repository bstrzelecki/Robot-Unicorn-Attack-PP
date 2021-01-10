#pragma once
#include "Prop.h"
#include "Platform.h"
#include <stdlib.h>
#include <cstdio>
#include "Player.h"
#include "Bonus.h"
#include <cstring>
#include "Star.h"
#include "CurvedPlatform.h"
class Scene: public Prop
{
public:
	Scene(Player* player);
	void HandleSettings(FILE* file);
	void SetupPlatform(int& count, FILE* file, int i);
	~Scene();
	// X motion
	void Move(int delta);
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual void Update(double delta) override;
	void TriggerDeath();
	int score=0;
	int scrollSpeed = BASE_SCROLLSPEED;
private:
	int deathFlag = 0;
	void MovePickups(double delta);
	void DeadlyCollisions(int i);
	void AddBonusPoints();
	void AddStarPoints();

	int spawnTimer = 0;

	int** groups;
	int* groupPointers;
	int groupCount = 0;
	int loopWidth;

	//Bonus Settings
	int bonusStreak = 1;
	int starStreak = 1;
	int displayedBonus = 0;
	double bonusTimer = 0;
	double bonusDuration = 1;

	// Speed settings
	double speedUpTimer = 0;
	double speedUpMaxtime = 10;
	int maxScrollSpeed = 10;
	
	int platformCount = 0;
	int isRandom = 1;
	Player* player;
	Platform** platforms;
};

