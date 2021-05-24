#include "Enemy_IceGolum.h"

/*************************************************************************************
*Constructor. Initializes the parameters needed
*
*@param none
*************************************************************************************/
IceGolum::IceGolum()
{
	groundLevel = 750;
	gPosition = sf::Vector2f(1800, groundLevel);
	velocity = sf::Vector2f(0, 0);
	spawnDelay = 5;

	InitAnimations();

	pAnimationScale = sf::Vector2f(-0.2f, 0.2f);
	animatedSprite = AnimatedSprite(sf::seconds(0.085), true, true);
	animatedSprite.setScale(pAnimationScale);
	animatedSprite.setPosition(gPosition);

	health = 100;

	srand(time(0));
	shootDelay = 3;
	bullets = new  Bullet(120, 85, 10, "./Resources/Images/Rock2.png");

	currentAnimation = &throwAnimation;

}

/*************************************************************************************
*Destructor
*************************************************************************************/
IceGolum::~IceGolum(){
}

void IceGolum::spawnEnemy() {
	if (lastEnemySpawned.getElapsedTime().asSeconds() >= spawnDelay) {
		animatedSprite.setPosition(gPosition);
		health = 100;
	}
}

void IceGolum::shoot(sf::Time deltaTime)
{
	if (lastBulletShot.getElapsedTime().asSeconds() >= shootDelay) {
		bullets->shoot(animatedSprite.getPosition(), deltaTime, false);
		lastBulletShot.restart();

		currentAnimation = &throwAnimation;
		isShooting = true;
	}
}

void IceGolum::move() {
	if (health > 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			animatedSprite.move(-6.f, 0.f);
		else
			animatedSprite.move(-3.f, 0.f);
	}
}

void IceGolum::update(sf::Time deltaTime) {
	if (health <= 0) {
		currentAnimation = &dyingAnimation;
		isDying = true;
		animationUpdate(deltaTime);
		bullets->deleteBullets();


		if (animationClock.getElapsedTime().asSeconds() >= 0.85) {
			animatedSprite.setPosition(gPosition);
		}

		spawnEnemy();
		return;
	}
	if (health > 0) {
		animationClock.restart();
		lastEnemySpawned.restart();
	}

	spawnEnemy();
	shoot(deltaTime);
	move();

	animationUpdate(deltaTime);
	bullets->update();
}

/*************************************************************************************
*Checks the collisions of the enemie's bullets with another entity
*
* @param spriteShape the enitity we want to check for possible collisions
*
* @return bool
*************************************************************************************/
bool IceGolum::checkCollision(sf::FloatRect spriteShape) {
	bool collision;
	collision = bullets->checkCollision(spriteShape);

	if (animatedSprite.getGlobalBounds().intersects(spriteShape)) {
		collision = true;

		health -= 50;
		animatedSprite.setPosition(animatedSprite.getPosition().x + 50, animatedSprite.getPosition().y);
		currentAnimation = &hurtAnimation;
	}

	return collision;
}

/*************************************************************************************
*Updates the animation that is currently played
* @param deltaTime Variable used to determine the time passed, so we know when to
*				   play the next sprite of the animation
*
* @return void
*************************************************************************************/
void IceGolum::animationUpdate(sf::Time deltaTime) {
	animatedSprite.play(*currentAnimation);
	animatedSprite.update(deltaTime);
}

/*************************************************************************************
*Initialize the skins for the character from the files
* @param choice Decides which character files to upload into variables
*
* @return void
*************************************************************************************/
void IceGolum::InitAnimations()
{
	//Attack - Throw
	this->pTexture1.loadFromFile("./Resources/Images/Golum1/Golem1RunThrowing.png");
	throwAnimation.setSpriteSheet(pTexture1);
	//Hurt
	this->pTexture2.loadFromFile("./Resources/Images/Golum1/Golem1Hurt.png");
	hurtAnimation.setSpriteSheet(pTexture2);
	//Dying
	this->pTexture3.loadFromFile("./Resources/Images/Golum1/Golem1Dying.png");
	dyingAnimation.setSpriteSheet(pTexture3);


	for (int it = 900; it <= 9900; it += 900) {
		throwAnimation.addFrame(sf::IntRect(it, 0, 900, 900));
		hurtAnimation.addFrame(sf::IntRect(it, 0, 900, 900));
		dyingAnimation.addFrame(sf::IntRect(it, 0, 900, 900));
	}

	throwAnimation.addFrame(sf::IntRect(0, 0, 900, 900));
	hurtAnimation.addFrame(sf::IntRect(0, 0, 900, 900));
	dyingAnimation.addFrame(sf::IntRect(0, 0, 900, 900));
}

/*************************************************************************************
*Renders the animations on the window
* @param window Where we want our player to be drawn
*
* @return void
*************************************************************************************/
void IceGolum::draw(sf::RenderWindow& window)
{
	window.draw(animatedSprite);

	bullets->draw(&window);
}

sf::FloatRect IceGolum::getEnemyGlobalBounds()
{
	return animatedSprite.getGlobalBounds();
}

void IceGolum::updateHealth(int addedHealth)
{
	this->health += addedHealth;
}

int IceGolum::getEnemyHealth()
{
	return health;
}
