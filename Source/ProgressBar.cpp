#include "ProgressBar.h"


ProgressBar::ProgressBar(float startX, float startY, const int X_OFFSET, const int Y_OFFSET, const int MAX_HEALTH,
						std::string fillImageStr)
	: MAX_VALUE(MAX_HEALTH), X_FILL_OFFSET(3), Y_FILL_OFFSET(2), BAR_X_OFFSET(X_OFFSET), BAR_Y_OFFSET(Y_OFFSET)
{
	//frameImage.loadFromFile(frameImageStr);
	fillImage.loadFromFile(fillImageStr);

	//frameSprite.setTexture(frameImage);
	fillSprite.setTexture(fillImage);

	showFill = true;

	this->startX = startX;
	this->startY = startY;

	//frameSprite.setPosition(startX + BAR_X_OFFSET, startY + BAR_Y_OFFSET);
	fillSprite.setPosition(startX + BAR_X_OFFSET + X_FILL_OFFSET, startY + BAR_Y_OFFSET + Y_FILL_OFFSET);
}


ProgressBar::~ProgressBar()
{
}

void ProgressBar::updateSprite(int currentValue)
{
	scaleX = (float(currentValue) / MAX_VALUE);
	fillSprite.setScale(scaleX, 1.f);

	if (currentValue <= 0)
		showFill = false;
	else
		showFill = true;
}

void ProgressBar::draw(sf::RenderWindow* renderWindow)
{
	frameSprite.setPosition(startX + BAR_X_OFFSET, startY + BAR_Y_OFFSET);
	fillSprite.setPosition(startX + BAR_X_OFFSET + X_FILL_OFFSET, startY + BAR_Y_OFFSET + Y_FILL_OFFSET);

	if (showFill == true)
		renderWindow->draw(fillSprite);

	renderWindow->draw(frameSprite);
}