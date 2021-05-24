#include "..\Includes\FinalBoss.h"

/*************************************************************************************
*Constructor. Initializes the parameters needed
* 
*@param none
*************************************************************************************/
FinalBoss::FinalBoss()
{
	jump = false;
	ground = true;
	groundLevel = 680; //depends on the scale :) - 780 for 3.5
	maxHeight = 550;
	jumpDelay = 5;
	bPosition = sf::Vector2f(2000, groundLevel);
	gravity = sf::Vector2f(0, 0.15);
	velocity= sf::Vector2f(0, 0);
	direction = -1;


	InitAnimations();

	pAnimationScale = sf::Vector2f(-0.75f, 0.75f);
	animatedSprite = AnimatedSprite(sf::seconds(0.085), true, true);
	animatedSprite.setScale(pAnimationScale);
	animatedSprite.setPosition(bPosition);

	health = 500;

	srand(time(0));
	minShootDelay = 100;
	maxShootDelay = 100;
	bullets = new  Bullet(200, 150, 18, "./Resources/Images/Rock2.png");


	isWaveCompleted = false;
	printWaveCompleted = false;
}

/*************************************************************************************
*Destructor
*************************************************************************************/
FinalBoss::~FinalBoss() {
}

void FinalBoss::spawnFinalBoss()
{
	if (animatedSprite.getPosition().x >= 1500) {
		animatedSprite.move(-1.f, 0.f);
	}

	if (animatedSprite.getPosition().x <= 1510) {
		minShootDelay = 2;
		maxShootDelay = 4;
	}
}

/*************************************************************************************
*The enemy is able to shoot only after a certain delay. If the condition is met, a 
* bullet is shot and the clock is restared.
*
*@param deltaTime gives the time passed since the last call
* 
* @return void
*************************************************************************************/
void FinalBoss::shoot(sf::Time deltaTime)
{
	randomShootDelay = rand() % (int)maxShootDelay + minShootDelay;

	if (lastBulletShot.getElapsedTime().asSeconds() >= randomShootDelay) {

		bullets->shoot(animatedSprite.getPosition(), deltaTime, false);
		lastBulletShot.restart();

		isShooting = true;
	}
}

/*************************************************************************************
*The enemy is able to move only within certain bounds, so it can have a "ghostly" 
* appearance
*
*@param none
*
* @return void
*************************************************************************************/
void FinalBoss::move() {

	if (groundLevel -20 <= animatedSprite.getPosition().y &&
		groundLevel >= animatedSprite.getPosition().y) {
		direction = -1;
	}
	if (maxHeight <= animatedSprite.getPosition().y &&
		maxHeight + 20 >= animatedSprite.getPosition().y) {
		direction = +1;
	}
	
	velocity.y = 1.5 * direction;
	animatedSprite.move(velocity);	
}

/*************************************************************************************
*Coordonates all the functions needed for the enemy to "function".
*
*@param deltaTime parameter needed to shoot a bullet.
*
* @return void
*************************************************************************************/
void FinalBoss::update(sf::Time deltaTime)
{
	//Game over
	if (health <= 0) {
		currentAnimation = &dyingAnimation;
		animationUpdate(deltaTime);
		bullets->deleteBullets();;

		if (animationClock.getElapsedTime().asSeconds() >= 1) {
			animatedSprite.setPosition(bPosition);
			printWaveCompleted = true;
		}

		if (animationClock.getElapsedTime().asSeconds() >= 10) {
			isWaveCompleted = true;
			printWaveCompleted = false;
		}

		return;
	}
	if (health > 0) 
		animationClock.restart();

	int randomVar = rand() % 100;
	if (randomVar <= 50)
		move();
	else
		shoot(deltaTime);

	currentAnimation = &idleAnimation;

	if (isShooting) {
		animatedSprite.stop();
		currentAnimation = &throwAnimation;

		isShooting = false;
	}


	animationUpdate(deltaTime);
	bullets->update();

}

/*************************************************************************************
*Updates the animation that is currently played
* @param deltaTime Variable used to determine the time passed, so we know when to
*				   play the next sprite of the animation
*
* @return void
*************************************************************************************/
void FinalBoss::animationUpdate(sf::Time deltaTime) {


	animatedSprite.play(*currentAnimation);
	animatedSprite.update(deltaTime);
}

/*************************************************************************************
*Checks the collisions of the enemie's bullets with another entity
*
* @param spriteShape the enitity we want to check for possible collisions
* 
* @return bool
*************************************************************************************/
bool FinalBoss::checkCollision(sf::FloatRect spriteShape) {
	return	bullets->checkCollision(spriteShape);
}

/*************************************************************************************
*Initialize the skins for the character from the files
* @param choice Decides which character files to upload into variables
*
* @return void
*************************************************************************************/
void FinalBoss::InitAnimations() {
	//Idle
	this->pTexture2.loadFromFile("./Resources/Images/Wraith/WraithIdle.png");
	idleAnimation.setSpriteSheet(pTexture2);
	//Attack - Throw
	this->pTexture3.loadFromFile("./Resources/Images/Wraith/WraithAttack.png");
	throwAnimation.setSpriteSheet(pTexture3);
	//Hurt
	this->pTexture4.loadFromFile("./Resources/Images/Wraith/WraithHurt.png");
	hurtAnimation.setSpriteSheet(pTexture4);
	//Dying
	this->pTexture5.loadFromFile("./Resources/Images/Wraith/WraithDying.png");
	dyingAnimation.setSpriteSheet(pTexture5);


	for (int it = 120; it <= 6000; it += 520) {
		throwAnimation.addFrame(sf::IntRect(it, 0, 280, 420));
		idleAnimation.addFrame(sf::IntRect(it, 0, 280, 420));
		hurtAnimation.addFrame(sf::IntRect(it, 0, 280, 420));
		dyingAnimation.addFrame(sf::IntRect(it, 0, 280, 420));
	}
}

/*************************************************************************************
*Renders the animations on the window
* @param window Where we want our player to be drawn
*
* @return void
*************************************************************************************/
void FinalBoss::renderBoss(sf::RenderWindow& window)
{
	window.draw(animatedSprite);
	
	bullets->draw(&window);
}

/*************************************************************************************
*Getter returning the global bounds of the sprite
*
*@param none
*
* @return FloatRect
*************************************************************************************/
sf::FloatRect FinalBoss::getFinalBossRect()
{
	return animatedSprite.getGlobalBounds();
}

void FinalBoss::updateHealth(int healthModifier) {
	health += healthModifier;
}

bool FinalBoss::getIsWaveCompleted()
{
	return isWaveCompleted;
}

bool FinalBoss::getPrintWaveCompleted()
{
	return printWaveCompleted;
}

void FinalBoss::setIsWaveCompleted(bool wave)
{
	isWaveCompleted = wave;
}
