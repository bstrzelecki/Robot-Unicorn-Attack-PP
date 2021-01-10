#include "FinalScore.h"

void FinalScore::Render(double delta, RenderBatch* batch)
{
	char totalScoreText[BUFFSIZE];
	sprintf(totalScoreText, "Your final score: %d", score);
	char nameText[BUFFSIZE];
	sprintf(nameText, "Name: %s", name);
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2, "You died");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + LINE_SPACEING * 1, "You have 0 lives remaining");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + LINE_SPACEING * 2, totalScoreText);
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + LINE_SPACEING * 3, nameText);
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + LINE_SPACEING * 4, "Press 'SPACE' to save or ',' to go to the menu");
}

void FinalScore::Update(double delta)
{
}
