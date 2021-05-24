#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

class ProgressBar
{
public:
	/**
	 * Constructor for initialising the class' properties.
	 * @param startX The initial x position of the bar
	 * @param startY The initial y position of the bar
	 * @param X_OFFSET The x offset from the initial x.
	 * @param Y_OFFSET The y offset from the intial y.
	 * @param MAX_HEALTH The maximum health value for use with scaling.
	 */
	/*ProgressBar(float startX, float startY, const int X_OFFSET, const int Y_OFFSET, 
				const int MAX_HEALTH, std::string frameImageStr, std::string fillImageStr);*/

	ProgressBar(float startX, float startY, const int X_OFFSET, const int Y_OFFSET,
		const int MAX_HEALTH, std::string fillImageStr);

	~ProgressBar();

	/** Renders the bar at the specified x and y location. */
	void draw(sf::RenderWindow* renderWindow);

	/** Scales the fillSprite based on the health parameter. */
	void updateSprite(int currentValue);

private:
	sf::Sprite frameSprite;
	sf::Sprite fillSprite;
	sf::Texture frameImage;
	sf::Texture fillImage;

	// Stores fillSprite specific offsets for rendering
	const int X_FILL_OFFSET;
	const int Y_FILL_OFFSET;

	// Stores the bar offsets for rendering
	const int BAR_X_OFFSET;
	const int BAR_Y_OFFSET;

	/** Stores the maximum possible health value of the player. */
	const int MAX_VALUE;

	/** Determines whether or not the fillSprite variable is rendered. */
	bool showFill;

	int startX, startY;

	float scaleX;
};