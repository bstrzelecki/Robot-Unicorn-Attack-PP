#include "Scene.h"

Scene::Scene(Player* player)
{
	this->player = player;
	platformCount = 3;
	loopWidth = 700;
	platforms = (Platform**)malloc(platformCount * sizeof(void*));
	if (platforms == nullptr) {
		platformCount = 0;
		return;
	}
	platforms[0] = new Platform(Point(150, 80));
	platforms[1] = new Platform(Point(500, 180));
	platforms[2] = new Platform(Point(250, 380));
}

Scene::~Scene()
{
	for (int i = 0; i < platformCount; i++) {
		delete platforms[i];
	}
	free(platforms);
}

void Scene::Move(int delta)
{
	for (int i = 0; i < platformCount; i++) {
		platforms[i]->Position.x -= delta;
		if (platforms[i]->Position.x + platforms[i]->Width < 0)
		{
			platforms[i]->Position.x = loopWidth;
		}
	}

}

void Scene::SetScrollingSpeed(int speed)
{
	scrollSpeed = speed;
}

void Scene::Render(double delta, RenderBatch* batch)
{
	for (int i = 0; i < platformCount; i++) {
		platforms[i]->Render(delta, batch);
	}
}

void Scene::Update(double delta)
{
	Move(scrollSpeed * player->isDashing?2:1);
	if (player->isDashing)
		return;
	for (int i = 0; i < platformCount; i++) {
		if (platforms[i]->TestCollision(player->bottomCollision.y) && !platforms[i]->TestCollision(player->collisionThreshold.y))
		{
			player->RestoreJumps();
			player->height = platforms[i]->Position.y - player->bottomCollision.y + player->height;
		}
	}
}
