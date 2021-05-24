#include "Bullet.h"

/*************************************************************************************
*Initialize the character skin in accordance with the choice selected in the menu
* @param offsetX moves the bullet on the Ox axis because characters are different and
*				 have individual "shooting points
*		 offsetY same thing, only for the Oy axis
*		 path	 the folder path to the bullet image
*************************************************************************************/
Bullet::Bullet(int offsetX, int offsetY, int speed, std::string path)
{
	//load texture
	texture.loadFromFile(path);
	bSprite.setTexture(texture);
	bSprite.setScale(2.f, 2.f);

	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->speed = speed;

	delay = 0.8;
}
/*************************************************************************************
*Default constructor
*************************************************************************************/
Bullet::Bullet() {
}

/*************************************************************************************
*Destructor
*************************************************************************************/
Bullet::~Bullet(){
}

/*************************************************************************************
*The players can shoot only after a certain delay. In this function, we check if we can 
* meet the condition for shooting a new bullet, and if true, we add it to the list
*We take into consideration the following:
*	@pPosition the current position of the player
*	@deltaTime variable used to measure the time passed
*	@faceRight there are 2 directions, and depending on which part the character is facing
*			   the bullet will be shot accordingly
*************************************************************************************/
void Bullet::shoot(sf::Vector2f pPosition , sf::Time deltaTime, bool faceRight)
{
	if (lastBulletShot.getElapsedTime().asSeconds() >= delay)
	{
		if (faceRight) {
			shootDirections.push_back(1);
			bSprite.setPosition(pPosition.x + offsetX , pPosition.y + offsetY);
		}
		else {
			bSprite.setPosition(pPosition.x - offsetX, pPosition.y + offsetY);
			shootDirections.push_back(-1);
		}
		bullets.push_back(bSprite);

		//Restart time
		lastBulletShot.restart();
	}
}

/*************************************************************************************
*This is where the bullets are moved, and, if they reach the end of the screen, they
* are removed from the list.
* @param none
* 
* @return void
*************************************************************************************/
void Bullet::update()
{

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].move(shootDirections[i] * speed, 0.f);

		if (bullets[i].getPosition().x >= 1650 || bullets[i].getPosition().x <= 0) {
			bullets.erase(bullets.begin() + i);
			shootDirections.erase(shootDirections.begin() + i);
		}

	}
}

/*************************************************************************************
*Auxiliary function used to determine if two objects are colliding
* @param bullet holds the position of the bullet we want to verify
*		 spriteShape any player/sprite we want to check 
* 
* @return bool
*************************************************************************************/
bool Bullet::isColliding(sf::FloatRect bullet,sf::FloatRect spriteShape) {

	if (bullet.intersects(spriteShape)) {
			return true;
	}

	return false;
}

/*************************************************************************************
*In this function we traverse the list of bullets and check if each of them has collided
* witht another object
* @param spriteShape the entity we need to check for collisions
*
* @return bool
*************************************************************************************/
bool Bullet::checkCollision(sf::FloatRect spriteShape) {
	for (int i = 0; i < bullets.size(); i++)
		if (isColliding(bullets[i].getGlobalBounds(), spriteShape)) {
			bullets.erase(bullets.begin() + i);
			shootDirections.erase(shootDirections.begin() + i);
			return true;
		}

	return false;
}

/*************************************************************************************
*Empties the list of bullets so when the player dies, they get removed from the screen
* 
* @param none
* 
* @return void
*************************************************************************************/
void Bullet::deleteBullets()
{
	bullets.clear();
}

/*************************************************************************************
*Draws all the bullets on the window
* @param renderWindow the window on which we want our bullets rendered
*
* @return void
*************************************************************************************/
void Bullet::draw(sf::RenderWindow* renderWindow)
{
	for (int i = 0; i < bullets.size(); i++) {
		renderWindow->draw(bullets[i]);
	}		
}
