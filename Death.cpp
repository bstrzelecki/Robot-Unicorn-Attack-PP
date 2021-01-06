#include "Death.h"

void Death::Render(double delta, RenderBatch* batch)
{
	char scoreText[256];
	sprintf(scoreText, "Score: %d", score);
	char livesText[256];
	sprintf(livesText, "Lives remaining: %d", lives);

	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2, "You died");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 10, scoreText);
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 +20, livesText);
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 +30,  "Press 'c' to continue or press 'm' to go to the menu");
} 

void Death::Update(double delta)
{
}
