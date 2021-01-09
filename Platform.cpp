#include "Platform.h"

Platform::Platform(Point start, Point size)
{
	Position = start;
	Width = size.x;
	Height = size.y;
	startingPosition = start;
	bonuses = new Platform * [BUFFSIZE];
	stars = new Platform * [BUFFSIZE];
	topCollider = new Collider(Width, Direction::Up);
	bottomCollider = new Collider(Width, Direction::Down);
}

Platform::~Platform()
{
	delete topCollider;
	delete bottomCollider;

	for (int i = 0; i < bonusCount; i++) {
		delete bonuses[i];
	}
	for (int i = 0; i < starCount; i++) {
		delete stars[i];
	}
	delete bonuses;
	delete stars;
}

int Platform::TestCollision(int playerY)
{
	if (topCollider->TestCollision(playerY, Position) &&
		bottomCollider->TestCollision(playerY, Point(Position.x, Position.y + Height)))
		return 1;
	else
		return 0;
}

void Platform::AddBonus(Platform* bonus)
{
	bonuses[bonusCount] = bonus;
	bonusCount++;
}

void Platform::AddStar(Platform* star)
{
	stars[starCount] = star;
	starCount++;
}

void Platform::Loop(int width)
{
	Position.x += width;
	isVisible = 1;
	for (int i = 0; i < bonusCount; i++) {
		bonuses[i]->Loop(width);
	}
	for (int i = 0; i < starCount; i++) {
		stars[i]->Loop(width);
	}
	Randomize();
}

void Platform::Randomize()
{
	ResetPickups(bonuses, bonusCount);
	ResetPickups(stars, starCount);
}

void Platform::ResetPickups(Platform** list, int count)
{
	for (int i = 0; i < count; i++) {
		list[i]->isVisible = 0;
	}
	int sb = rand() % (count + SPAWN_CHANCE_OFFSET);
	if (sb < count) {
		list[sb]->isVisible = 1;
	}
}

void Platform::Render(double delta, RenderBatch* batch)
{
	if (!isVisible)return;
	batch->DrawRectangle(Position.x, Position.y, Width, Height, RED, GREEN);
	DrawPickup(bonuses, bonusCount, delta, batch);
	DrawPickup(stars, starCount, delta, batch);
}

void Platform::DrawPickup(Platform** list, int count , double delta, RenderBatch* batch)
{
	for (int i = 0; i < count; i++) {
		list[i]->Render(delta, batch);
	}
}

void Platform::Update(double delta)
{
	UpdatePickup(bonuses, bonusCount);
	UpdatePickup(stars, starCount);
}

void Platform::UpdatePickup(Platform** list, int count)
{
	for (int i = 0; i < count; i++) {
		list[i]->Position = Point(list[i]->startingPosition.x + Position.x, list[i]->startingPosition.y + Position.y);
	}
}
