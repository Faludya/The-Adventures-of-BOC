#pragma once
#include "Bullet.h"
#include <AnimatedSprite.h>

class FinalBoss {
public:
	FinalBoss();
	~FinalBoss();
	void spawnFinalBoss();
	void update(const sf::Time deltaTime);
	void shoot(const sf::Time deltaTime);
	void move();
	void renderBoss(sf::RenderWindow& window);
	void animationUpdate(const sf::Time deltaTime);
	bool checkCollision(sf::FloatRect spriteShape);
	sf::FloatRect getFinalBossRect();
	void updateHealth(int healthModifier);
	bool getIsWaveCompleted();
	bool getPrintWaveCompleted();
	void setIsWaveCompleted(bool wave);

private:
	sf::Texture bossTexture;
	sf::Sprite bossSprite;
	sf::Texture pTexture1, pTexture2, pTexture3,
				pTexture4, pTexture5, pTexture6;
	Animation idleAnimation, throwAnimation, hurtAnimation,
			  jumpAnimation, dyingAnimation;
	sf::Vector2f pAnimationScale;
	sf::Sprite bSprite;
	Animation* currentAnimation;
	AnimatedSprite animatedSprite;
	sf::Vector2f bPosition;

	int health;

	int minShootDelay;
	int maxShootDelay;
	float randomShootDelay;
	sf::Clock lastBulletShot;
	Bullet* bullets;

	int jumpDelay;
	bool jump;
	bool ground;
	float groundLevel;
	int maxHeight;
	int direction;
	sf::Clock lastJump;
	sf::Vector2f velocity;
	sf::Vector2f gravity;

	sf::Clock animationClock;
	bool isDying, isHurt, isShooting;
	bool isWaveCompleted;
	bool printWaveCompleted;
//Functions
	void InitAnimations();
};