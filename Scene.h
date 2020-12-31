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
private:
	int scrollSpeed = 1;
	int loopWidth;
	int platformCount = 0;
	Player* player;
	Platform** platforms;
};

