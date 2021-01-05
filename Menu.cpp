#include "Menu.h"

void Menu::Render(double delta, RenderBatch* batch)
{
	batch->DrawString(30, 30, "Unicorn");
	batch->DrawString(30, 60, "Press 'n' to play!");
}

void Menu::Update(double delta)
{
}
