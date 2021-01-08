#include "Platform.h"

Platform::Platform(Point start, Point size)
{
	Position = start;
	Width = size.x;
	Height = size.y;
	startingPosition = start;
	bonuses = new Platform * [BUFFSIZE];
	stars = new Platform * [BUFFSIZE];
	topCollider = new Collider(Width, Up);
	bottomCollider = new Collider(Width, Down);
}

Platform::~Platform()
{
	delete topCollider;
	delete bottomCollider;
}

int Platform::TestCollision(int playerY)
{
	if (topCollider->TestCollision(playerY, Position) &&
		bottomCollider->TestCollision(playerY, Point(Position.x, Position.y + Height)))
		return 1;
	else
		return 0;
}

void Platform::Reset()
{
	Position = startingPosition;
	for (int i = 0; i < bonusCount; i++) {
		bonuses[i]->Reset();
	}
	for (int i = 0; i < starCount; i++) {
		stars[i]->Reset();
	}
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
	Position.x = width;
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
	for (int i = 0; i < bonusCount; i++) {
		bonuses[i]->isVisible = 0;
	}
	for (int i = 0; i < starCount; i++) {
		stars[i]->isVisible = 0;
	}
	int bb = rand() % (bonusCount + 3);
	int sb = rand() % (starCount + 3);
	if (bb < bonusCount) {
		bonuses[bb]->isVisible = 1;
	}
	if (sb < starCount) {
		stars[sb]->isVisible = 1;
	}

}

void Platform::Render(double delta, RenderBatch* batch)
{
	if (!isVisible)return;
	batch->DrawRectangle(Position.x, Position.y, Width, Height, 0xff0000, 0x00ff00);
	for (int i = 0; i < bonusCount; i++) {
		bonuses[i]->Render(delta,batch);
	}
	for (int i = 0; i < starCount; i++) {
		stars[i]->Render(delta, batch);
	}
}

void Platform::Update(double delta)
{
	for (int i = 0; i < bonusCount; i++) {
		bonuses[i]->Position = Point(bonuses[i]->startingPosition.x + Position.x,bonuses[i]->startingPosition.y + Position.y);
	}
	for (int i = 0; i < starCount; i++) {
		stars[i]->Position = Point(stars[i]->startingPosition.x + Position.x, stars[i]->startingPosition.y + Position.y);
	}
}
