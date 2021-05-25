#include "MainMenu.h"

MainMenu::MainMenu() : window(sf::VideoMode(width, height), "The Adventures of BOC")
{
	if (!font.loadFromFile("resources/fonts/arial.ttf"))
	{

	}
	srand(time(0));
	level = new Level();

	randomBackground = rand() % 6;

	selectedItem = 0;

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("New game");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Load game");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Quit game");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
}

MainMenu::~MainMenu()
{

}

void MainMenu::loop()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					moveUp();
					break;

				case sf::Keyboard::Down:
					moveDown();
					break;

				case sf::Keyboard::Return:
					switch (selectedItem)
					{
					case 0:
						printf("Play button has been pressed\n");
						newGame();
						break;
					case 1:
						printf("Load button has been pressed\n");
						loadGame();
						break;
					case 2:
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;
			}
		}

		window.clear();
		draw(window);
		window.display();
	}
}

void MainMenu::newGame()
{
	window.close();
	
	SelectCharacterMenu* selectCharacter = new SelectCharacterMenu();
	selectCharacter->loop();
}

void MainMenu::loadGame()
{
	window.close();

	Game game(3);
	game.loadGame();
	game.loop();
}

void MainMenu::draw(sf::RenderWindow& window)
{
	level->draw(&window);

	for (auto& it : menu)
	{
		window.draw(it);
	}
}

void MainMenu::moveUp()
{
	if (selectedItem >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

void MainMenu::moveDown()
{
	if (selectedItem <= MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}
