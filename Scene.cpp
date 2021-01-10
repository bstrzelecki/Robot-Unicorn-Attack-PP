#include "Scene.h"

// Scene file
// p? - deafult platform (x y width height randomnessGroup randomnessOffset bonusBufferSize starBufferSize)
// b! - bonus (x y 0 0)
// s! - star (x y 0 0)
// c? - curved platform (x y width height a b c randomnessGroup randomnessOffset bonusBufferSize starBufferSize)


Scene::Scene(Player* player)
{
	this->player = player;

	FILE* file = fopen("scene.txt", "r");
	HandleSettings(file);
	for (int i = -1; i < platformCount;) {
		int x, y, width, height;
		char mode[BUFFSIZE] = "";
		int count = 0;
		count = fscanf(file, "%s %d %d %d %d", mode, &x, &y,&width,&height);
		if (count != 5)break;
		if (strcmp(mode, "p?")==0) {
			i++;
			platforms[i] = new Platform(Point(x, y), Point(width, height));
			SetupPlatform(count, file, i);
		} else if (strcmp(mode, "c?") == 0) {
			i++;
			int a, b, c;
			count = fscanf(file, " %d %d %d", &a, &b, &c);
			if (count != 3)break;
			platforms[i] = new CurvedPlatform(Point(x, y), Point(width, height),a,b,c);
			SetupPlatform(count, file, i);
		}
		if (strcmp(mode, "b!")==0) {
			platforms[i]->AddBonus(new Bonus(Point(x, y)));
		}
		if (strcmp(mode, "s!")==0) {
			platforms[i]->AddStar(new Star(Point(x, y)));
		}
	}
	if (isRandom) {
		for (int i = 1; i < platformCount; i++) {
			platforms[i]->Position.x = -2 * SCREEN_WIDTH;
			platforms[i]->isVisible = 0;
		}
	}
	fclose(file);
}

void Scene::HandleSettings(FILE* file)
{
	char validator[BUFFSIZE] = "";
	int buff = 0;
	groupCount = 0;
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
		if (strcmp(validator, "random:") == 0) {
			isRandom = buff;
		}
		if (strcmp(validator, "groups:") == 0) {
			groupCount = buff;
		}
	}
	groups = new int* [groupCount];
	groupPointers = new int[groupCount];
	for (int i = 0; i < groupCount; i++) {
		groupPointers[i] = 0;
	}
	for (int i = 0; i < groupCount; i++) {
		groups[i] = new int[GROUP_SIZE];
		for (int j = 0; j < GROUP_SIZE; j++) {
			groups[i][j] = -1;
		}
	}
	platformCount = buff;
	platforms = new Platform * [platformCount];
	if (platforms == nullptr) {
		platformCount = 0;
		return;
	}
}

void Scene::SetupPlatform(int& count, FILE* file, int i)
{
	int groupId = 0;
	int randomOffset = 0;
	count = fscanf(file, "%d %d", &groupId, &randomOffset);
	if (count != 2) { return; };
	platforms[i]->randomOffset = randomOffset;
	groups[groupId][groupPointers[groupId]] = i;
	groupPointers[groupId]++;
	int bStar, bBonus;
	count = fscanf(file, "%d %d", &bStar, &bBonus);
	if (count != 2) { return; };
	platforms[i]->SetBuffers(bBonus, bStar);
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
	spawnTimer += delta;
	for (int i = 0; i < platformCount; i++) {
		platforms[i]->Position.x -= delta;
		if (platforms[i]->Position.x + platforms[i]->Width < 0 && platforms[i]->isVisible)
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
			if(!isRandom)
				platforms[i]->Loop(loopWidth);
		}
	}
	if (spawnTimer >= SCREEN_WIDTH * 2 && isRandom) {
		int rng = rand() % groupCount;
		int offset = (rand() % 100 - 50);
		for (int j = 0; j < GROUP_SIZE; j++) {
			if (groups[rng][j] == -1)break;
			platforms[groups[rng][j]]->Loop(SCREEN_WIDTH - platforms[groups[rng][j]]->Position.x + platforms[groups[rng][j]]->randomOffset + offset);
		}
		spawnTimer = 0;
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
	if (speedUpTimer > speedUpMaxtime && scrollSpeed < maxScrollSpeed && scrollSpeed != 0) {
		scrollSpeed++;
		speedUpTimer = 0;
	}
	MovePickups(delta);
	for (int i = 0; i < platformCount; i++) {
		if (!platforms[i]->isVisible)continue;
		platforms[i]->Position.y = platforms[i]->startingPosition.y - player->height;
	}
	for (int i = 0; i < platformCount; i++) {
		if (!platforms[i]->isVisible)continue;
		if (platforms[i]->TestCollision(player->bottomCollision.y) && !platforms[i]->TestCollision(player->bottomCollisionThreshold.y))
		{
			player->RestoreJumps();
			player->isFalling = 0;
			player->ApplyMove(platforms[i]->GetY() - player->bottomCollision.y);
		}
		if (platforms[i]->TestCollision(player->topCollision.y) && !platforms[i]->TestCollision(player->topCollisionThreshold.y))
		{
			player->ApplyMove(platforms[i]->GetY() + platforms[i]->Height - player->topCollision.y);
		}
		DeadlyCollisions(i);
	}
	if (player->height + player->offset > SCENE_HEIGHT + SCREEN_HEIGHT / 2) {
		TriggerDeath();
	}
	for (int i = 0; i < platformCount; i++) {
		if (!platforms[i]->isVisible)continue;
		platforms[i]->Position.y = platforms[i]->startingPosition.y - player->height;

	}
}

void Scene::MovePickups(double delta)
{
	for (int i = 0; i < platformCount; i++) {
		if (!platforms[i]->isVisible)continue;
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
