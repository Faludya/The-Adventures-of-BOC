#pragma once
#include "Player.h"

class Level
{
public:
    //Constructor & Destructor
    Level();
    ~Level();
    //Functions used in Game
    void draw(sf::RenderWindow* window);
    void update(bool isPlayerAtFinalBoss);

    void setBackgroundIndex(int backgroundIndex);
    int getBackgroundIndex();

private:
    sf::Texture backgroundTexture1, backgroundTexture2, backgroundTexture3, 
                backgroundTexture4, backgroundTexture5, backgroundTexture6;
    sf::Sprite backgrounds[6];
    sf::Vector2f position;

    int backgroundIndex;

    bool isAtFinalBoss;

    //Utility functions
    void initBackgrounds();
};