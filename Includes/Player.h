#pragma once
#include "AnimatedSprite.h"
#include "ProgressBar.h"
#include "Bullet.h"

class Player
{
public:
	//Functions called in Game
	Player(int choice);
	void keyboardInput(sf::Time deltaTime);
	void update(int frames);
	void renderPlayer(sf::RenderWindow&window);
	bool checkCollision(sf::FloatRect enemy);
	sf::FloatRect getPlayerBounds();
	void updateHealth(int addedHealth);
	bool getIsAtFinalBoss();

	void setPlayerHealth(int playerHealth);
	int getPlayerHealth();
	void setPlayerPoints(int playerPoints);
	int getPlayerPoints();
	void addPoints();
protected:
	//Animations and Textures
	sf::Texture pTexture1, pTexture2, pTexture3, 
				pTexture4, pTexture5, pTexture6;
	Animation idleAnimation, throwAnimation, hurtAnimation,
		      jumpAnimation, runAnimation;
	sf::Vector2f pAnimationScale;
	bool faceRight;
	//Actual player
	sf::Sprite pSprite;
	Animation* currentAnimation;
	AnimatedSprite animatedSprite;
	AnimatedSprite animatedFrameBar;
	//Movement
	sf::Vector2f pPosition;
	sf::Vector2f velocity;
	sf::Vector2f gravity;
	sf::IntRect rect;
	int t;
	bool jump;
	bool ground;
	float groundLevel;
	//Health
	const int MAX_HEALTH = 500;
	int health;
	sf::Vector2f healthBarPosition;
	ProgressBar* healthBar;
	//Points
	const int MAX_POINTS = 1000;
	int points;
	sf::Vector2f pointsBarPosition;
	ProgressBar* pointsBar;
	//Bullet
	Bullet* bullets;
	//Player Frame
	sf::Sprite frameSprite;
	sf::Texture frameImage;
	//Image Player Frame
	sf::Sprite frameBarSprite;
	sf::Texture frameBarImage;

	bool isAtFinalBoss;
	
	//Utility functions
	void InitAnimations(int choice);
	void animationUpdate(sf::Time deltaTime);
};

