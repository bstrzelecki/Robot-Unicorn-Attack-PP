#include "Menu.h"

#define TITLE_X 30
#define TITLE_Y 30

#define COM_Y 60

void Menu::Render(double delta, RenderBatch* batch)
{
	batch->DrawString(TITLE_X, TITLE_Y, "Unicorn");
	batch->DrawString(TITLE_X, COM_Y, "Press 'n' to play!");
}

void Menu::Update(double delta)
{
}
