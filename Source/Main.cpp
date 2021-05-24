#include "Game.h"
#include "MainMenu.h"

int main()
{
	MainMenu* mainMenu = new MainMenu();
	mainMenu->loop();

	return 0;
}