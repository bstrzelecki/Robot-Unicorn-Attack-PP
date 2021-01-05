#include "FinalScore.h"

void FinalScore::Render(double delta, RenderBatch* batch)
{
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2, "You died");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 10, "You have 0 lives remaining");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 20, "Your final score: 0");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 30, "Name:");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 40, "Press '.' to save or ',' to go to the menu");
}

void FinalScore::Update(double delta)
{
}
