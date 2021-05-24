#pragma once
#pragma once
#include "AnimatedSprite.h"
#include "Bullet.h"
#include <string>

class LavaGolum {
public:
	LavaGolum();
	~LavaGolum();
	void shoot(sf::Time deltaTime);
	void move();
	void update(sf::Time deltaTime);
	bool checkCollision(sf::FloatRect spriteShape);
	void spawnEnemy();
	void animationUpdate(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);
	sf::FloatRect getEnemyGlobalBounds();
	void updateHealth(int addedHealth);
	int getEnemyHealth();
private:
	sf::Texture golumTexture;
	sf::Sprite golumSprite;
	sf::Texture pTexture1, pTexture2, pTexture3;
	Animation  throwAnimation, hurtAnimation,
		dyingAnimation;
	sf::Vector2f pAnimationScale;
	sf::Sprite gSprite;
	Animation* currentAnimation;
	AnimatedSprite animatedSprite;
	sf::Vector2f gPosition;

	int shootDelay;
	float randomShootDelay;
	sf::Clock lastBulletShot;
	Bullet* bullets;

	int health;
	float groundLevel;
	sf::Vector2f velocity;

	sf::Clock lastEnemySpawned;
	sf::Clock animationClock;
	int spawnDelay;

	bool isDying, isHurt, isShooting;

	//Functions
	void InitAnimations();
};