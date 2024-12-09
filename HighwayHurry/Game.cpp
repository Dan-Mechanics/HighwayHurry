#include "Game.h"
#include "Time.h"
#include "Player.h"
#include "Environment.h"
//#include <iostream>
//#include <string>
#include "Utils.h"
#include "Scoreboard.h"
#include "Button.h"
#include "Obstacle.h"
#include <random>

//use this->more !
//use{} with initilzaer list
//use default
//always virtual destructor
//    {
//}
//public
//protected
//private

// pointer is like int? in c# and references are handy because then you have
// a contract saying you must give me a value, pointers is acceptable behaviour no value.

//Game::Game(sf::RenderWindow& window, sf::Font& font, Time& time, Score& score) :
//    window{ window }, font{ font }, time{ time }, score{ score } { }

Game::Game() = default;

/// <summary>
/// Be really really really really careful with memory here.
/// </summary>
bool Game::play(sf::RenderWindow & window, sf::Sprite & playerSprite, sf::Sprite & backgroundSprite, sf::Sprite & obstacleSprite, Score & score, Time & time, Scoreboard & scoreboard)
{
    print("Opening game.");

    Player player{ window, playerSprite };
    Environment environment{ window, backgroundSprite };

    std::vector<Entity*> entities;

    entities.push_back(&environment);
    entities.push_back(&player);

    std::vector<Obstacle*> obstacles;

    // i basically want this to be dynaically allocated in this heap scope, 
    // and i also want to add more cars so progresllively more difficult.
    // i have no idea how im gonna add friction and or collison !!!
    for (int i = 0; i < 8; i++)
    {
        // DNAGER DANGER ZONE.
        Obstacle* car = new Obstacle(window, obstacleSprite, score);

        obstacles.push_back(car);

        // ?? entities.emplace_back(window, playerSprite);
    }

    score.reset();
    time.reset();

    while (window.isOpen())
    {
        // we do this hereb ecause we dont want a dead window for the draw .. ??
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (checkExitCondition(event))
            {
                window.close();

                print("Exiting game.");

                // This is good I think.
                for (int i = 0; i < obstacles.size(); i++)
                {
                    delete obstacles[i];
                }

                obstacles.clear();

                return true;
            }
        }

        for (int i = 0; i < time.processFrame(); i++)
        {
            for (int j = 0; j < entities.size(); j++)
            {
                entities[j]->move(time);
            }

            for (int j = 0; j < obstacles.size(); j++)
            {
                obstacles[j]->move(time);

                if (player.checkCollision(score, *obstacles[j]))
                {
                    for (int i = 0; i < obstacles.size(); i++)
                    {
                        delete obstacles[i];
                    }

                    obstacles.clear();
                    
                    // here we wanna go to next scene bascially.
                    return false;

                    // https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index
                    // vec.erase(vec.begin() + index);

                    // no not this.
                    //obstacles.erase(obstacles.begin() + j);

                    //obstacles[j]->ResetPosition();
                }
            }
        }

        // so that we see where holes and transparency.
        window.clear(sf::Color::Magenta);

        environment.draw(window, backgroundSprite);

        for (int i = 0; i < obstacles.size(); i++)
        {
            obstacles[i]->draw(window, obstacleSprite);
        }

        player.draw(window, playerSprite);

        scoreboard.draw(window, score);

        window.display();
    }

    // This is good I think.
    for (int i = 0; i < obstacles.size(); i++)
    {
        delete obstacles[i];
    }

    obstacles.clear();

    print("Closing game.");

    return false;
}