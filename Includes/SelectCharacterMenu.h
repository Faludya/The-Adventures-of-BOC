#pragma once
#include "Game.h"

#define MAX_NUMBER_OF_ITEMS 3

class SelectCharacterMenu
{
public:
	SelectCharacterMenu();
	~SelectCharacterMenu();

	void loop();

	int width = 1600;
	int height = 900;

private:
	sf::RenderWindow window;
	sf::Font font;

	Level* level;
	int randomBackground;

	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	int selectedItem;

	sf::Texture texture1, texture2, texture3;
	sf::Sprite character1, character2, character3;

	void draw(sf::RenderWindow& window);
	void moveLeft();
	void moveRight();

	void createNewSession(int n);
};