#pragma once
#include "SelectCharacterMenu.h"

#define MAX_NUMBER_OF_ITEMS 3

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void loop();

	void newGame();
	void loadGame();

	int width = 1600;
	int height = 900;

	int randomBackground;
	
private:
	sf::RenderWindow window;
	sf::Font font;

	Level* level;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	int selectedItem;

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
};