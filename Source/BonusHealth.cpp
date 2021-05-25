#include "..\Includes\BonusHealth.h"
#include <SFML\Window\Keyboard.hpp>
/*************************************************************************************
*Constructor.
*
* @param none
*************************************************************************************/
BonusHealth::BonusHealth()
{
	srand(time(0));

	healthTexture.loadFromFile("./Resources/Images/life.png");
	healthSprite.setTexture(healthTexture);
	healthSprite.setScale(0.1f, 0.1f);

	minHeight = 550;
	maxHeight = 780;
	chance = 35;
	delay = 30;

	isOnScreen = false;
	healthSprite.setPosition(1650, 600);

	isAtFinalBoss = false;
}
/*************************************************************************************
* Destructor
*************************************************************************************/
BonusHealth::~BonusHealth()
{
}

/*************************************************************************************
*Life will appear randomly but only a certain delay. The height at which it appears is
*determined randomly, but between the ground and the max height at which the player
* can jump.
* 
* @param none
*************************************************************************************/
void BonusHealth::spawnHealth()
{
	if (lastHealth.getElapsedTime().asSeconds() >= delay) {
		int randomChance = rand() % 100;

		if (randomChance <= chance) {
			randomHeight = rand() % maxHeight + minHeight;
			healthSprite.setPosition(1650, randomHeight);

			isOnScreen = true;
			lastHealth.restart();
		}
	}
}

/*************************************************************************************
*Decides the movement of the sprite. If went out of the screen (left) it remains at the 
* same position. If the screen is moving the speed must be doubled to mentain the same
* moving effect.
*
* @param none
*************************************************************************************/
void BonusHealth::move()
{
	if (healthSprite.getGlobalBounds().left <= -healthSprite.getGlobalBounds().width - 10) {
		isOnScreen = false;
	}
	else
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isAtFinalBoss)
			healthSprite.move(-8, 0);
		else
			healthSprite.move(-4, 0);
}

// TODO : if i print the position it seems that it resets it and its moving but is is not rendered?
//printf("%f\n", healthSprite.getGlobalBounds().left);


/*************************************************************************************
*Used to update all the functions that change the state of the sprite
*
* @param none
*************************************************************************************/
void BonusHealth::update(bool isPlayerAtFinalBoss)
{
	isAtFinalBoss = isPlayerAtFinalBoss;
	spawnHealth();
	move();
}

//TODO : make it work plez :c
/*************************************************************************************
*Checks if the life is colliding with any other entity
*
* @param spriteShape its of type FloatRect because its a subtype for many containers used
* 
* @return true if a collision has been detected
*************************************************************************************/
bool BonusHealth::checkCollision(sf::FloatRect spriteShape)
{
	sf::FloatRect lifeRect = healthSprite.getGlobalBounds();
	if (lifeRect.intersects(spriteShape)) {
		isOnScreen = false;
		healthSprite.setPosition(-healthSprite.getGlobalBounds().width - 10, 600);
		lastHealth.restart();

		return true;
	}

	return false;
}

/*************************************************************************************
*Renders the life on the window
* 
* @param window Where we want our background to be drawn
*************************************************************************************/
void BonusHealth::draw(sf::RenderWindow& window)
{
	window.draw(this->healthSprite);
}

