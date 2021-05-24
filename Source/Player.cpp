#include "Player.h"

/*************************************************************************************
*Initialize the character skin in accordance with the choice selected in the menu
* @param choice The number corresponding to one of the 3 skins:
*		#1 for owlet
*		#2 for pink
*		#3 for blue
*************************************************************************************/
Player::Player(const int choice) : velocity(0, 0), gravity(0, 0.50), rect(0, 0, 32, 32)
{
	//Movement related initializations
	groundLevel = 780;
	faceRight = true;
	jump = false;
	ground = true;
	t = 0;
	isAtFinalBoss = false;

	//Player related initializations
	pPosition = sf::Vector2f(32, groundLevel);
	pAnimationScale = sf::Vector2f(3.5f, 3.5f);
	animatedSprite = AnimatedSprite(sf::seconds(0.2), true, true);
	animatedSprite.setPosition(pPosition);
	animatedSprite.setScale(pAnimationScale);

	animatedFrameBar.setScale(sf::Vector2f(3.5f, 3.5f));
	animatedFrameBar.setPosition(40, 40);

	// Create the frame of the player
	frameImage.loadFromFile("./Resources/Images/HealthFrame.png");
	frameSprite.setTexture(frameImage);
	frameSprite.setPosition(10, 10);

	// Create the points of frame
	points = 0;
	pointsBar = new ProgressBar(10, 10, 140, 110, MAX_POINTS, "./Resources/Images/HealthFrameGreen.png");
	pointsBar->updateSprite(points);

	// Create the health of frame
	health = 500;
	healthBar = new ProgressBar(10, 10, 162, 74, health, "./Resources/Images/HealthFrameRed.png");
	
	//Initialize bullets
	bullets = new  Bullet(64, 45, 8, "./Resources/Images/Rock2.png");

	InitAnimations(choice);
}

/*************************************************************************************
*Initialize the skins for the character from the files
* @param choice Decides which character files to upload into variables
*
* @return void
*************************************************************************************/
void Player::InitAnimations(const int choice) {
	switch (choice)
	{
	case 1:
		//Default Sprite
		this->pTexture1.loadFromFile("./Resources/Images/Owlet/Owlet_Monster.png");
		this->pSprite.setTexture(pTexture1);
		//Idle
		this->pTexture2.loadFromFile("./Resources/Images/Owlet/Owlet_Monster_Idle_4.png");
		idleAnimation.setSpriteSheet(pTexture2);
		//Attack - Throw
		this->pTexture3.loadFromFile("./Resources/Images/Owlet/Owlet_Monster_Throw_4.png");
		throwAnimation.setSpriteSheet(pTexture3);
		//Hurt
		this->pTexture4.loadFromFile("./Resources/Images/Owlet/Owlet_Monster_Hurt_4.png");
		hurtAnimation.setSpriteSheet(pTexture4);
		//Run
		this->pTexture5.loadFromFile("./Resources/Images/Owlet/Owlet_Monster_Run_6.png");
		runAnimation.setSpriteSheet(pTexture5);
		//Jump
		this->pTexture6.loadFromFile("./Resources/Images/Owlet/Owlet_Monster_Jump_8.png");
		jumpAnimation.setSpriteSheet(pTexture6);

		break;
	case 2:
		//Default Sprite
		this->pTexture1.loadFromFile("./Resources/Images/Pinky/Pink_Monster.png");
		this->pSprite.setTexture(pTexture1);
		//Idle 
		this->pTexture2.loadFromFile("./Resources/Images/Pinky/Pink_Monster_Idle_4.png");
		idleAnimation.setSpriteSheet(pTexture2);
		//Attack - Throw
		this->pTexture3.loadFromFile("./Resources/Images/Pinky/Pink_Monster_Throw_4.png");
		throwAnimation.setSpriteSheet(pTexture3);
		//Hurt
		this->pTexture4.loadFromFile("./Resources/Images/Pinky/Pink_Monster_Hurt_4.png");
		hurtAnimation.setSpriteSheet(pTexture4);
		//Run
		this->pTexture5.loadFromFile("./Resources/Images/Pinky/Pink_Monster_Run_6.png");
		runAnimation.setSpriteSheet(pTexture5);
		//Jump
		this->pTexture6.loadFromFile("./Resources/Images/Pinky/Pink_Monster_Jump_8.png");
		jumpAnimation.setSpriteSheet(pTexture6);

		break;
	case 3:
		//Default Sprite
		this->pTexture1.loadFromFile("./Resources/Images/Dude/Dude_Monster.png");
		this->pSprite.setTexture(pTexture1);
		//Idle
		this->pTexture2.loadFromFile("./Resources/Images/Dude/Dude_Monster_Idle_4.png");
		idleAnimation.setSpriteSheet(pTexture2);
		//Attack - Throw
		this->pTexture3.loadFromFile("./Resources/Images/Dude/Dude_Monster_Throw_4.png");
		throwAnimation.setSpriteSheet(pTexture3);
		//Hurt
		this->pTexture4.loadFromFile("./Resources/Images/Dude/Dude_Monster_Hurt_4.png");
		hurtAnimation.setSpriteSheet(pTexture4);
		//Run
		this->pTexture5.loadFromFile("./Resources/Images/Dude/Dude_Monster_Run_6.png");
		runAnimation.setSpriteSheet(pTexture5);
		//Jump
		this->pTexture6.loadFromFile("./Resources/Images/Dude/Dude_Monster_Jump_8.png");
		jumpAnimation.setSpriteSheet(pTexture6);
		break;
	}

	idleAnimation.addFrame(sf::IntRect(32, 0, 32, 32));
	idleAnimation.addFrame(sf::IntRect(64, 0, 32, 32));
	idleAnimation.addFrame(sf::IntRect(96, 0, 32, 32));
	idleAnimation.addFrame(sf::IntRect(0, 0, 32, 32));

	throwAnimation.addFrame(sf::IntRect(32, 0, 32, 32));
	throwAnimation.addFrame(sf::IntRect(64, 0, 32, 32));
	throwAnimation.addFrame(sf::IntRect(96, 0, 32, 32));
	throwAnimation.addFrame(sf::IntRect(0, 0, 32, 32));

	hurtAnimation.addFrame(sf::IntRect(32, 0, 32, 32));
	hurtAnimation.addFrame(sf::IntRect(64, 0, 32, 32));
	hurtAnimation.addFrame(sf::IntRect(96, 0, 32, 32));
	hurtAnimation.addFrame(sf::IntRect(0, 0, 32, 32));

	runAnimation.addFrame(sf::IntRect(32, 0, 32, 32));
	runAnimation.addFrame(sf::IntRect(64, 0, 32, 32));
	runAnimation.addFrame(sf::IntRect(96, 0, 32, 32));
	runAnimation.addFrame(sf::IntRect(128, 0, 32, 32));
	runAnimation.addFrame(sf::IntRect(160, 0, 32, 32));
	runAnimation.addFrame(sf::IntRect(0, 0, 32, 32));

	jumpAnimation.addFrame(sf::IntRect(32, 0, 32, 32));
	jumpAnimation.addFrame(sf::IntRect(64, 0, 32, 32));
	jumpAnimation.addFrame(sf::IntRect(96, 0, 32, 32));
	jumpAnimation.addFrame(sf::IntRect(128, 0, 32, 32));
	jumpAnimation.addFrame(sf::IntRect(160, 0, 32, 32));
	jumpAnimation.addFrame(sf::IntRect(192, 0, 32, 32));
	jumpAnimation.addFrame(sf::IntRect(224, 0, 32, 32));
	jumpAnimation.addFrame(sf::IntRect(0, 0, 32, 32));

}


/*************************************************************************************
*Processes what happens when a certain key is pressed
*	#changes velocity and animations
*	#shoots
* @param none
* @return void
*************************************************************************************/
void Player::keyboardInput(const sf::Time deltaTime)
{
	currentAnimation = &idleAnimation;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && ground)
	{
		this->velocity.y = -15;
		jump = true;
		ground = false;

		currentAnimation = &jumpAnimation;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		faceRight = true;
		currentAnimation = &runAnimation;

		if(isAtFinalBoss && pPosition.x <= 1510)
			this->velocity.x = 6;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		faceRight = false;
		currentAnimation = &runAnimation;

		if (isAtFinalBoss && pPosition.x >= 90)
			this->velocity.x = -6;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		//shoot bullet
		currentAnimation = &throwAnimation;
		bullets->shoot(pPosition, deltaTime, faceRight);
	}

	this->animationUpdate(deltaTime);
}

/*************************************************************************************
*Updates elements related to movement
*	#positin
*	#velocity
*	#frames
*	#checks collisions?
* @param frames Keeps the frame rate exact
* @param enemy Checks collisions with enemies?
*
* @return void
*************************************************************************************/
void Player::update(const int frames) {
	//Game over
	if (health <= 0) {
		
		return;
	}

	//Movement updates
	pPosition += velocity;
	if (!ground)
	{
		velocity += gravity;

		if (pPosition.y >= groundLevel)
		{
			pPosition.y = groundLevel;
			ground = true;
			jump = false;
			velocity.y = 0;
		}
	}
	//I dont know what this is doing :)
	rect = sf::IntRect(t, 0, 50, 43);
	if (frames % 12 == 0)
		t = (t + 50) % 100;

	if (ground)
		velocity = sf::Vector2f(0, 0);


	animatedSprite.setPosition(pPosition);
	bullets->update();

	//If we complete the wave
	if (points >= 1000)
		isAtFinalBoss = true;
}

/*************************************************************************************
*Updates the animation that is currently played
* @param deltaTime Variable used to determine the time passed, so we know when to
*				   play the next sprite of the animation
*
* @return void
*************************************************************************************/
void Player::animationUpdate(const sf::Time deltaTime) {
	//changing the scale will move the sprite, but for some reason it didn't work when
	//I called the function setPosition, so I modified the position itself,
	//but *4 becouse (idk why) otherwise it moved the sprite on the far left
	sf::Vector2f oldPlayerPos = animatedSprite.getPosition();

	if (faceRight == false) {
		animatedSprite.setScale(-fabs(pAnimationScale.x), pAnimationScale.y);
		if (!isAtFinalBoss)
			pPosition.x = pSprite.getGlobalBounds().height * 4;
		else
			pPosition.x = oldPlayerPos.x;
	}
	else {
		animatedSprite.setScale(fabs(pAnimationScale.x), pAnimationScale.y);
		if (!isAtFinalBoss)
			pPosition.x = pSprite.getGlobalBounds().height;
		else
			pPosition.x = oldPlayerPos.x;
	}

	animatedSprite.play(*currentAnimation);
	animatedSprite.update(deltaTime);

	animatedFrameBar.play(*(&jumpAnimation));
	animatedFrameBar.update(deltaTime);
}

/*************************************************************************************
*Checks if the player is colliding with another entity
* @param enemy the rectangle containing the bounds of the entity
*
* @return bool
*************************************************************************************/
bool Player::checkCollision(sf::FloatRect enemy) 
{
	bool collision;
	collision = bullets->checkCollision(enemy);

	if (animatedSprite.getGlobalBounds().intersects(enemy)) {
		collision = true;

		updateHealth(-20);
		animatedSprite.setPosition(animatedSprite.getPosition().x - 50, animatedSprite.getPosition().y);
		currentAnimation = &hurtAnimation;

	}

	return collision;
}

/*************************************************************************************
*Renders the animations on the window
* @param window Where we want our player to be drawn
*
* @return void
*************************************************************************************/
void Player::renderPlayer(sf::RenderWindow& window) {
	window.draw(this->animatedSprite);

	healthBar->draw(&window);
	pointsBar->draw(&window);

	window.draw(frameBarSprite);
	window.draw(frameSprite);

	bullets->draw(&window);

	window.draw(this->animatedFrameBar);
}

/*************************************************************************************
*If the player collides with an entity, the function is called to modify it. There are 
* two cases:
*	#player collides with the bonus health ==> health is added
*	#player collides with enemy ==> health is taken
* Since the only difference is the sign, when health is taken it will be multiplied with
* (-1) when the function is called
* !OBS : The player cannot exceed the maximum health.
* @param bonusHealth the bonus health added to the player's current health
*
* @return void
*************************************************************************************/
void Player::updateHealth(int addedHealth)
{
	if (this->health + addedHealth <= +MAX_HEALTH)
		this->health += addedHealth;
	else
		this->health = MAX_HEALTH;
	healthBar->updateSprite(health);
}

/*************************************************************************************
*Getter used to inform other entities that the player is at the final boss
* @param none
*
* @return bool
*************************************************************************************/
bool Player::getIsAtFinalBoss()
{
	return this->isAtFinalBoss;
}

void Player::setPlayerHealth(int playerHealth)
{
	health = playerHealth;
	healthBar->updateSprite(health);
}

int Player::getPlayerHealth()
{
	return health;
}

void Player::setPlayerPoints(int playerPoints)
{
	points = playerPoints;
	pointsBar->updateSprite(points);
}

int Player::getPlayerPoints()
{
	return points;
}

void Player::addPoints()
{
	if(points + 100 <= MAX_POINTS)
		points += 100;
	pointsBar->updateSprite(points);
}

/*************************************************************************************
*Getter used to check collisions of other enitites with the player
* @param none
*
* @return FloatRect
*************************************************************************************/
sf::FloatRect Player::getPlayerBounds()
{
	return animatedSprite.getGlobalBounds();
}