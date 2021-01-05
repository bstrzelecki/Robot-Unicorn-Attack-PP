#include "Death.h"

void Death::Render(double delta, RenderBatch* batch)
{
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2, "You died");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 10, "Score: 0");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 +20, "Lives remaining: 2");
	batch->DrawString(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 +30,  "Press 'c' to continue or press 'm' to go to the menu");
} 

void Death::Update(double delta)
{
}
