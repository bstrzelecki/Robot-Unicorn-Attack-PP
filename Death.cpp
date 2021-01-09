#include "Death.h"

void Death::Render(double delta, RenderBatch* batch)
{
	char scoreText[BUFFSIZE];
	sprintf(scoreText, "Score: %d", score);
	char livesText[BUFFSIZE];
	sprintf(livesText, "Lives remaining: %d", lives);

	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2, "You died");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + LINE_SPACEING, scoreText);
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + LINE_SPACEING * 2, livesText);
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + LINE_SPACEING * 3,  "Press 'c' to continue or press 'm' to go to the menu");
} 

void Death::Update(double delta)
{
}
