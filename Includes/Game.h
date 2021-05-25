#pragma once
#include "Player.h"
#include "ProgressBar.h"
#include "Level.h"
#include "BonusHealth.h"
#include "FinalBoss.h"
#include "Enemy_IceGolum.h"
#include "Enemy_DirtGolum.h"
#include "Enemy_LavaGolum.h"


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

    void resetWave();
private:
    sf::Time deltaTime;

    sf::RenderWindow window;
    Player* player;
    Animation* currentAnimation;

    int frames;

    Level level;
    BonusHealth* bonusHealth;

    IceGolum* iceGolum;
    DirtGolum* dirtGolum;
    LavaGolum* lavaGolum;

    FinalBoss* finalBoss;
    bool isFinalBoss;

    int characterSkin;
    int waveNumber;

    sf::Font font;
    sf::Text messageWaveCompleted;
    sf::Text messageWaveNumber;
    sf::Text messageGameOver;
    sf::Clock gameOverTime;
    bool isGameOver;

    void resetIfPlayerDead();
    void keyboardInput();
    void printMessages();
};