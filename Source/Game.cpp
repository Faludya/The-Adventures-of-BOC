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

    bonusHealth = new BonusHealth();

    isFinalBoss = false;

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
    frames = ((frames + 1) % 60) + 1;

    //Entities update
    level.update(player->getIsAtFinalBoss());
    player->keyboardInput(this->deltaTime);
    player->update(frames);
    bonusHealth->update(player->getIsAtFinalBoss());

    //FinalBoss
    isFinalBoss = player->getIsAtFinalBoss();
    if (isFinalBoss) {
        finalBoss->spawnFinalBoss();
        finalBoss->update(deltaTime);
    }


    //Collisions
    checkCollisions();
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

    //FinalBoss
    if(isFinalBoss)
        finalBoss->renderBoss(window);

    window.display();
}

 void Game::checkCollisions()
 {
     //healthBonus - Player
     if (bonusHealth->checkCollision(player->getPlayerBounds()))
         player->updateHealth(40);

     if (isFinalBoss) {
         //Player - FinalBoss
         if (player->checkCollision(finalBoss->getFinalBossRect()))
             finalBoss->updateHealth(-25);

         //FinalBoss bullets - Player
         if (finalBoss->checkCollision(player->getPlayerBounds()))
             player->updateHealth(-100);
     }
     //TODO : collision between healthBonus and bullets make it dissapear
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

     saveData << player->getPlayerHealth() << "\n" << player->getPlayerPoints() << "\n";
     saveData << isFinalBoss << "\n";
     saveData << level.getBackgroundIndex() << "\n";
 }

 void Game::loadGame()
 {
     int playerHealth, playerPoints, background;
     bool finalBoss;

     saveData >> playerHealth >> playerPoints;
     saveData >> finalBoss;
     saveData >> background;

     player->setPlayerHealth(playerHealth);
     player->setPlayerPoints(playerPoints);
     isFinalBoss = finalBoss;
     level.setBackgroundIndex(background);
 }
