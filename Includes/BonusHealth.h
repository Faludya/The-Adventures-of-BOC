#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

class BonusHealth {
public:
	BonusHealth();
	~BonusHealth();
	void update(bool isPlayerAtFinalBoss);
	void spawnHealth();
	void move();
	bool checkCollision(sf::FloatRect spriteShape);
	void draw(sf::RenderWindow& window);

private:
	sf::Texture healthTexture;
	sf::Sprite healthSprite;
	int minHeight;
	int maxHeight;
	int randomHeight;

	int chance;
	bool isOnScreen;
	
	float delay;
	sf::Clock lastHealth;

	bool isAtFinalBoss;
};