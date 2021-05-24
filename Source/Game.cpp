#include "Game.h"
#include <fstream>

std::fstream saveData("./Resources/data.txt");

/*************************************************************************************
*Initialize the game elements and size of the window
* @param characterSkin Decides which character skin will be used in the game
*************************************************************************************/
 Game::Game(const int characterSkin) : window(sf::VideoMode(1600, 900) , "The Adventures of BOC")
{
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2,
                       sf::VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));

    frames = 0;

    player = new Player(characterSkin);
    finalBoss = new FinalBoss();
    iceGolum = new IceGolum();
    dirtGolum = new DirtGolum();
    lavaGolum = new LavaGolum();
    bonusHealth = new BonusHealth();

    isFinalBoss = false;
    this->characterSkin = characterSkin;
    waveNumber = 1;

    if (!font.loadFromFile("resources/fonts/DreamePatter.ttf")) {
    }

    messageWaveCompleted.setFont(font);
    messageWaveCompleted.setFillColor(sf::Color::Black);
    messageWaveCompleted.setCharacterSize(100);
    messageWaveCompleted.setStyle(sf::Text::Bold);
    messageWaveCompleted.setPosition(500, 300);
    messageWaveCompleted.setString("Wave Completed");

    messageGameOver.setFont(font);
    messageGameOver.setFillColor(sf::Color::Red);
    messageGameOver.setCharacterSize(100);
    messageGameOver.setStyle(sf::Text::Bold);
    messageGameOver.setPosition(500, 300);
    messageGameOver.setString("Game Over");

    messageWaveNumber.setFont(font);
    messageWaveNumber.setFillColor(sf::Color::White);
    messageWaveNumber.setCharacterSize(40);
    messageWaveNumber.setStyle(sf::Text::Bold);
    messageWaveNumber.setPosition(200, 35);

    isGameOver = false;
}

 /*************************************************************************************
* Destructor
*************************************************************************************/
 Game::~Game(){
}

 /*************************************************************************************
*Main game loop. All the major events are handled here, along with the clock and all
* the functions needed to keep the game running are called here
* 
* @param none
* @return void
*************************************************************************************/
 void Game::loop()
{
     sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        keyboardInput();
        update();
        render();

    }
}

 /*************************************************************************************
*All the objects call their update functions here
* 
* @param none
* @return void
*************************************************************************************/
 void Game::update()
{
    //Next Wave
     if (finalBoss->getIsWaveCompleted()) {
         resetWave();
         waveNumber++;
         finalBoss->setIsWaveCompleted(false);
     }

     resetIfPlayerDead();

    frames = ((frames + 1) % 60) + 1;

    //Entities update
    level.update(player->getIsAtFinalBoss());
    player->keyboardInput(this->deltaTime);
    player->update(frames);
    bonusHealth->update(player->getIsAtFinalBoss());

    //Enemies - !FinalBoss
    if (!isFinalBoss) {
        iceGolum->update(deltaTime);
        dirtGolum->update(deltaTime);
        lavaGolum->update(deltaTime);
    }
    
    //FinalBoss
    isFinalBoss = player->getIsAtFinalBoss();
    if (isFinalBoss) {
        finalBoss->spawnFinalBoss();
        finalBoss->update(deltaTime);
    }


    //Collisions
    checkCollisions();
}

 void Game::resetIfPlayerDead() {
     if(player->getPlayerHealth() <= 0)
         isGameOver = true;

     //Leave some time for the message and player (so as not to restart instantly)
     if (player->getPlayerHealth() > 0) {
         gameOverTime.restart();
     }

     if (gameOverTime.getElapsedTime().asSeconds() >= 3.5) {
         isGameOver = false;
         resetWave();
         waveNumber = 1;
     }
 }

 /*************************************************************************************
*Draws all the objects on the window
* 
* @param none
* @return void
*************************************************************************************/
 void Game::render()
{
    window.clear(sf::Color(200, 200, 200));

    level.draw(&window);

    bonusHealth->draw(window);

    player->renderPlayer(window);

    //!FinalBoss
    if (!isFinalBoss) {
        iceGolum->draw(window);
        dirtGolum->draw(window);
        lavaGolum->draw(window);
    }

    //FinalBoss
    if(isFinalBoss)
        finalBoss->renderBoss(window);

    printMessages();

    window.display();

}

 void Game::printMessages()
 {
     //Draw wave completed
     if (finalBoss->getPrintWaveCompleted()) {
         window.draw(messageWaveCompleted);
     }

     messageWaveNumber.setString("Wave " + std::to_string(waveNumber));

     window.draw(messageWaveNumber);

     if (isGameOver)
         window.draw(messageGameOver);
 }


 void Game::checkCollisions()
 {
     //healthBonus - Player
     if (bonusHealth->checkCollision(player->getPlayerBounds()))
         player->updateHealth(40);

     if (!isFinalBoss) {
         //IceGolum - Player
         if (iceGolum->checkCollision(player->getPlayerBounds()))
             player->updateHealth(-100);
         //Player - IceGolum
         if (player->checkCollision(iceGolum->getEnemyGlobalBounds())) {
             iceGolum->updateHealth(-50);
             if (iceGolum->getEnemyHealth() <= 0)
                 player->addPoints();
         }
         //--------------------------------------------------------------
         //DirtGolum - Player
         if (dirtGolum->checkCollision(player->getPlayerBounds()))
             player->updateHealth(-100);
         //Player - DirtGolum
         if (player->checkCollision(dirtGolum->getEnemyGlobalBounds())) {
             dirtGolum->updateHealth(-50);
             if (dirtGolum->getEnemyHealth() <= 0)
                 player->addPoints();
         }
         //--------------------------------------------------------------
         //LavaGolum - Player
         if (lavaGolum->checkCollision(player->getPlayerBounds()))
             player->updateHealth(-100);
         //Player - LavaGolum
         if (player->checkCollision(lavaGolum->getEnemyGlobalBounds())) {
             lavaGolum->updateHealth(-50);
             if (lavaGolum->getEnemyHealth() <= 0)
                 player->addPoints();
         }
     }

     if (isFinalBoss) {
         //Player - FinalBoss
         if (player->checkCollision(finalBoss->getFinalBossRect()))
             finalBoss->updateHealth(-25);

         //FinalBoss bullets - Player
         if (finalBoss->checkCollision(player->getPlayerBounds()))
             player->updateHealth(-100);
     }
 }

 void Game::keyboardInput()
 {
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
     {
         saveGame();
     }
 }

 void Game::saveGame()
 {
     saveData.clear();

     saveData << characterSkin << "\n";
     saveData << player->getPlayerHealth() << "\n" << player->getPlayerPoints() << "\n";
     saveData << isFinalBoss << "\n";
     saveData << waveNumber << "\n";
     saveData << level.getBackgroundIndex() << "\n";
 }

 void Game::loadGame()
 {
     int playerSkin, playerHealth, playerPoints, background, waveNo;
     bool finalBoss;

     saveData >> playerSkin;
     saveData >> playerHealth >> playerPoints;
     saveData >> finalBoss;
     saveData >> waveNo;
     saveData >> background;

     delete player;
     player = new Player(playerSkin);

     player->setPlayerHealth(playerHealth);
     player->setPlayerPoints(playerPoints);
     isFinalBoss = finalBoss;
     waveNumber = waveNo;
     level.setBackgroundIndex(background);
 }

 void Game::resetWave()
 {
     delete player;
     player = new Player(characterSkin);

     delete finalBoss;
     finalBoss = new FinalBoss();

     delete iceGolum;
     iceGolum = new IceGolum();

     delete dirtGolum;
     dirtGolum = new DirtGolum();

     delete lavaGolum;
     lavaGolum = new LavaGolum();

     delete bonusHealth;
     bonusHealth = new BonusHealth();

     int nextLevel = (level.getBackgroundIndex() + 1) % 6;
     level.setBackgroundIndex(nextLevel);

 }
