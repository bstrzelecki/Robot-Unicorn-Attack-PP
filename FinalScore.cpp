#include "FinalScore.h"

void FinalScore::Render(double delta, RenderBatch* batch)
{
	char totalScoreText[256];
	sprintf(totalScoreText, "Your final score: %d", score);
	char nameText[256];
	sprintf(nameText, "Name: %s", name);
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2, "You died");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 10, "You have 0 lives remaining");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 20, totalScoreText);
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 30, nameText);
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 40, "Press '.' to save or ',' to go to the menu");
}

void FinalScore::Update(double delta)
{
}

void FinalScore::AddChar(char* c)
{
	
}
