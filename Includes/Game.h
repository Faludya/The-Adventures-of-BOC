#pragma once
#include "Player.h"
#include "ProgressBar.h"
#include "Level.h"
#include "BonusHealth.h"
#include "FinalBoss.h"

//#include "CollisionUtilities.h"
//#include "Obstacles.h"


class Game
{
public:
    Game(int characterSkin);
    ~Game();
    void loop();
    void update();
    void render();
    void checkCollisions();

    
    void saveGame();
    void loadGame();

private:
    sf::Time deltaTime;

    sf::RenderWindow window;
    Player* player;
    Animation* currentAnimation;

    int frames;

    Level level;
    BonusHealth* bonusHealth;

    FinalBoss* finalBoss;
    bool isFinalBoss;

    void keyboardInput();
};