#include "SelectCharacterMenu.h"

SelectCharacterMenu::SelectCharacterMenu() : window(sf::VideoMode(width, height), "The Adventures of BOC")
{
	if (!font.loadFromFile("resources/fonts/arial.ttf"))
	{

	}
	srand(time(0));
	level = new Level();
	randomBackground = rand() % 6;
	level->setBackgroundIndex(randomBackground);

	texture1.loadFromFile("./Resources/Images/Dude/Dude_Monster.png");
	texture2.loadFromFile("./Resources/Images/Owlet/Owlet_Monster.png");
	texture3.loadFromFile("./Resources/Images/Pinky/Pink_Monster.png");

	character1.setTexture(texture1);
	character2.setTexture(texture2);
	character3.setTexture(texture3);

	character1.setScale(6.f, 6.f);
	character1.setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 20, height / 2 - 200));

	character2.setScale(6.f, 6.f);
	character2.setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 20, height / 2 - 200));

	character3.setScale(6.f, 6.f);
	character3.setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 3 - 20, height / 2 - 200));

	selectedItem = 0;

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Character 1");
	menu[0].setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 1, height / 2));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Character 2");
	menu[1].setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 2, height / 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Character 3");
	menu[2].setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 3, height / 2));
}

SelectCharacterMenu::~SelectCharacterMenu()
{

}

void SelectCharacterMenu::loop()
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
				case sf::Keyboard::Left:
					moveLeft();
					break;

				case sf::Keyboard::Right:
					moveRight();
					break;

				case sf::Keyboard::Return:
					switch (selectedItem)
					{
					case 0:
						printf("Character 1 has been pressed\n");
						createNewSession(3);
						break;
					case 1:
						printf("Character 2 has been pressed\n");
						createNewSession(1);
						break;
					case 2:
						printf("Character 3 has been pressed\n");
						createNewSession(2);
						break;
					case 3:
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

void SelectCharacterMenu::createNewSession(int n)
{
	window.close();

	Game game(n);
	game.loop();
}

void SelectCharacterMenu::draw(sf::RenderWindow& window)
{
	level->draw(&window);

	for (auto& it : menu)
	{
		window.draw(it);
	}

	window.draw(character1);
	window.draw(character2);
	window.draw(character3);
}

void SelectCharacterMenu::moveLeft()
{
	if (selectedItem >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

void SelectCharacterMenu::moveRight()
{
	if (selectedItem <= MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}
