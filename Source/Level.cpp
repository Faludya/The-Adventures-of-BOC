#include "Level.h"

/*************************************************************************************
*Constructor.
*
* @param none
*************************************************************************************/
Level::Level()
{
    backgroundIndex = 0;

    position = sf::Vector2f(backgrounds[backgroundIndex].getPosition());

    initBackgrounds();

    srand(time(0));
    backgroundIndex = rand() % 6;

    isAtFinalBoss = false;
}

/*************************************************************************************
*Initializes all the backgrounds from file and adds them to the array
*   #at the end the backgroundIndex will be 5
*
* @param none
* @return void
*************************************************************************************/
void Level::initBackgrounds() {

    //Index 0 - forest and waterfall
    backgroundTexture1.loadFromFile("./Resources/Images/game_background_4.png");
    backgroundTexture1.setRepeated(true);
    backgrounds[backgroundIndex].setTexture(backgroundTexture1);
    
    //Index 1 - night forest
    backgroundIndex++;

    backgroundTexture2.loadFromFile("./Resources/Images/game_background_3.2.png");
    backgroundTexture2.setRepeated(true);
    backgrounds[backgroundIndex].setTexture(backgroundTexture2);

    //Index 2 - cartoon forest (thin trees)
    backgroundIndex++;

    backgroundTexture3.loadFromFile("./Resources/Images/Cartoon_Forest_BG_01.png");
    backgroundTexture3.setRepeated(true);
    backgrounds[backgroundIndex].setTexture(backgroundTexture3);

    //Index 3 - cartoon forest - blue lights
    backgroundIndex++;

    backgroundTexture4.loadFromFile("./Resources/Images/Cartoon_Forest_BG_02.png");
    backgroundTexture4.setRepeated(true);
    backgrounds[backgroundIndex].setTexture(backgroundTexture4);

    //Index 4 - cartoon forest (thicker trees)
    backgroundIndex++;

    backgroundTexture5.loadFromFile("./Resources/Images/Cartoon_Forest_BG_03.png");
    backgroundTexture5.setRepeated(true);
    backgrounds[backgroundIndex].setTexture(backgroundTexture5);

    //Index 5 - cartoon forest - colourful lights
    backgroundIndex++;

    backgroundTexture6.loadFromFile("./Resources/Images/Cartoon_Forest_BG_04.png");
    backgroundTexture6.setRepeated(true);
    backgrounds[backgroundIndex].setTexture(backgroundTexture6);
}

/*************************************************************************************
* Destructor
*************************************************************************************/
Level::~Level() {
}

/*************************************************************************************
*Updates all the elements concerning the background
*   #the image moves only while we press D
*       *the player cannot go back during waves
* @param none
* @return void
*************************************************************************************/
void Level::update(bool isPlayerAtFinalBoss)
{
    this->isAtFinalBoss = isPlayerAtFinalBoss;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isAtFinalBoss)
        position.x = position.x - 4;

    if (position.x == -1920)
        position.x = 0;

    backgrounds[backgroundIndex].setPosition(position);

    position = sf::Vector2f(backgrounds[backgroundIndex].getPosition());

}

/*************************************************************************************
*Renders the backgrounds on the window
* @param window Where we want our background to be drawn
*
* @return void
*************************************************************************************/ 
void Level::draw(sf::RenderWindow * window)
{
    window->draw(backgrounds[backgroundIndex]);
}


void Level::setBackgroundIndex(int backgroundIndex)
{
    this->backgroundIndex = backgroundIndex;
}

int Level::getBackgroundIndex()
{
    return backgroundIndex;
}