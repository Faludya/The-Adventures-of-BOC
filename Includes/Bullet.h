#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <SFML\Graphics\RenderWindow.hpp>

class Bullet {

public:
	Bullet();
	Bullet(int offsetX, int offsetY,int speed, std::string path);
	~Bullet();
	void update();
	void draw(sf::RenderWindow* renderWindow);
	void shoot(sf::Vector2f pPosition, sf::Time deltaTime, bool faceRight);
	bool isColliding(sf::FloatRect bullet, sf::FloatRect spriteShape);
	bool checkCollision(sf::FloatRect spriteShape);
	void deleteBullets();

private:
	sf::Texture texture;
	sf::Sprite bSprite;
	sf::Vector2f position;

	std::vector<sf::Sprite> bullets;
	std::vector<int> shootDirections;

	int offsetX;
	int offsetY;
	float delay;
	int speed;
	sf::Clock lastBulletShot;
};