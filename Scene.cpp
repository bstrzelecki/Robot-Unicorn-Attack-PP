#include "Scene.h"

Scene::Scene(Player* player)
{
	this->player = player;

	FILE* file = fopen("scene.txt", "r");
	char validator[BUFFSIZE]="";
	int buff = 0;
	loopWidth = 700;
	while (strcmp(validator, "platforms:"))
	{
		int count = 0;
		count = fscanf(file, "%s %d", validator, &buff);
		if (count != 2) {
			break;
		}
		if (strcmp(validator, "loop:") == 0) {
			loopWidth = buff;
		}
	}
	platformCount = buff;
	platforms = new Platform*[platformCount];
	if (platforms == nullptr) {
		platformCount = 0;
		return;
	}
	for (int i = -1; i < platformCount;) {
		int x, y, width, height;
		char mode[BUFFSIZE] = "";
		int count = 0;
		count = fscanf(file, "%s %d %d %d %d", mode, &x, &y,&width,&height);
		if (count != 5)break;
		if (strcmp(mode, "p?")==0) {
			i++;
			platforms[i] = new Platform(Point(x, y), Point(width, height));
		}
		if (strcmp(mode, "b!")==0) {
			platforms[i]->AddBonus(new Bonus(Point(x, y)));
		}
		if (strcmp(mode, "s!")==0) {
			platforms[i]->AddStar(new Star(Point(x, y)));
		}
	}
	fclose(file);
}

Scene::~Scene()
{
	for (int i = 0; i < platformCount; i++) {
		delete platforms[i];
	}
}

void Scene::Move(int delta)
{
	score += delta;
	for (int i = 0; i < platformCount; i++) {
		platforms[i]->Position.x -= delta;
		if (platforms[i]->Position.x + platforms[i]->Width < 0)
		{
			int visibleBonuses = 0;
			int visibleStars = 0;
			for (int j = 0; j < platforms[i]->bonusCount; j++) {
				if (platforms[i]->bonuses[j]->isVisible)
				{
					visibleBonuses++;
					platforms[i]->bonuses[j]->isVisible = 0;
				}
			}
			for (int j = 0; j < platforms[i]->starCount; j++) {
				if (platforms[i]->stars[j]->isVisible)
				{
					visibleStars++;
					platforms[i]->stars[j]->isVisible = 0;
				}
			}
			if (visibleBonuses > 0)
				bonusStreak = 1;
			if (visibleStars > 0)
				starStreak = 1;
			platforms[i]->Loop(loopWidth);
		}
	}

}

void Scene::Render(double delta, RenderBatch* batch)
{
	for (int i = 0; i < platformCount; i++) {
		platforms[i]->Render(delta, batch);
	}
	if (displayedBonus != 0) {
		char scoreText[BUFFSIZE];
		sprintf(scoreText, "%d", displayedBonus);
		batch->DrawString(150, SCREEN_HEIGHT / 2, scoreText);
	}
}

void Scene::Update(double delta)
{
	if (displayedBonus != 0) {
		bonusTimer += delta;
		if (bonusTimer >= bonusDuration) {
			displayedBonus = 0;
		}
	}
	if (deathFlag)
		return;
	Move(scrollSpeed * (player->isDashing?2:1) * delta * 100);
	speedUpTimer += delta;
	if (speedUpTimer > speedUpMaxtime && scrollSpeed < maxScrollSpeed) {
		scrollSpeed++;
		speedUpTimer = 0;
	}
	MovePickups(delta);
	if (player->isDashing)
		return;
	for (int i = 0; i < platformCount; i++) {
		platforms[i]->Position.y = platforms[i]->startingPosition.y - player->height;
	}
	for (int i = 0; i < platformCount; i++) {
		if (platforms[i]->TestCollision(player->bottomCollision.y) && !platforms[i]->TestCollision(player->bottomCollisionThreshold.y))
		{
			player->RestoreJumps();
			player->isFalling = 0;
			player->ApplyMove(platforms[i]->Position.y - player->bottomCollision.y);
		}
		else {
			player->isFalling = 1;
		}
		if (platforms[i]->TestCollision(player->topCollision.y) && !platforms[i]->TestCollision(player->topCollisionThreshold.y))
		{
			player->ApplyMove(platforms[i]->Position.y + platforms[i]->Height - player->topCollision.y);
		}
		DeadlyCollisions(i);
	}
	for (int i = 0; i < platformCount; i++) {
		platforms[i]->Position.y = platforms[i]->startingPosition.y - player->height;

	}
}

void Scene::MovePickups(double delta)
{
	for (int i = 0; i < platformCount; i++) {
		platforms[i]->Update(delta);
		for (int j = 0; j < platforms[i]->bonusCount; j++) {
			if (platforms[i]->bonuses[j]->TestCollision(player->bottomCollision.y) ||
				platforms[i]->bonuses[j]->TestCollision(player->bottomCollisionThreshold.y) ||
				platforms[i]->bonuses[j]->TestCollision(player->topCollision.y) ||
				platforms[i]->bonuses[j]->TestCollision(player->topCollisionThreshold.y)) {
				if (platforms[i]->bonuses[j]->isVisible) {
					AddBonusPoints();
					platforms[i]->bonuses[j]->isVisible = 0;
				}
			}
		}
		for (int j = 0; j < platforms[i]->starCount; j++) {
			if (platforms[i]->stars[j]->TestCollision(player->bottomCollision.y) ||
				platforms[i]->stars[j]->TestCollision(player->bottomCollisionThreshold.y) ||
				platforms[i]->stars[j]->TestCollision(player->topCollision.y) ||
				platforms[i]->stars[j]->TestCollision(player->topCollisionThreshold.y)) {
				if (platforms[i]->stars[j]->isVisible) {
					if (player->isDashing) {
						AddStarPoints();
						platforms[i]->stars[j]->isVisible = 0;
					}
					else {
						TriggerDeath();
					}
				}
			}
		}
	}
}

void Scene::DeadlyCollisions(int i)
{
	if (platforms[i]->TestCollision(player->bottomCollision.y) && platforms[i]->TestCollision(player->bottomCollisionThreshold.y))
	{
		TriggerDeath();
	}
	if (platforms[i]->TestCollision(player->topCollision.y) && platforms[i]->TestCollision(player->topCollisionThreshold.y))
	{
		TriggerDeath();
	}
	if (!platforms[i]->TestCollision(player->bottomCollision.y) && platforms[i]->TestCollision(player->bottomCollisionThreshold.y))
	{
		TriggerDeath();
	}
	if (!platforms[i]->TestCollision(player->topCollision.y) && platforms[i]->TestCollision(player->topCollisionThreshold.y))
	{
		TriggerDeath();
	}
}

void Scene::TriggerDeath()
{
	scrollSpeed = 0;
	deathFlag = 1;
	player->Kill();
}

void Scene::AddBonusPoints()
{
	int points = BONUS_POINTS * bonusStreak;
	displayedBonus = points;
	score += points;
	bonusTimer = 0;
	bonusStreak++;
}

void Scene::AddStarPoints()
{
	int points = STAR_POINTS * starStreak;
	displayedBonus = points;
	score += points;
	bonusTimer = 0;
	starStreak++;
}
