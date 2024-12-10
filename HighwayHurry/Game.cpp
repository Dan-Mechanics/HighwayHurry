#include "Game.h"
#include "Time.h"
#include "Player.h"
#include "Environment.h"
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

Game::Game(sf::RenderWindow & window, Score & score, Time & time, sf::Sprite & playerSprite, sf::Sprite & backgroundSprite, sf::Sprite & obstacleSprite, const sf::Font& const font) :
    playerSprite{ playerSprite }, backgroundSprite{ backgroundSprite }, obstacleSprite{ obstacleSprite } {
    print("Opening game.");

    // this makes the random fixed ? yep.

    player = { window, playerSprite };
    environment = { window, backgroundSprite };
    scoreboard = { font };
    //std::vector<Obstacle*> obstacles;

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

    refresh(score, time);
}

void Game::refresh(Score& score, Time& time) {
    srand(std::time(0));

    player.reset();
    score.reset();
    time.reset();

    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles[i]->resetPosition();
    }
}

std::string Game::update(sf::RenderWindow & window, Score& score, Time& time) {
    for (int i = 0; i < time.processFrame(); i++) {
        environment.move(time);
        player.move(time);

        for (int j = 0; j < obstacles.size(); j++) {
            obstacles[j]->move(time);

            if (player.checkCollision(score, *obstacles[j])) {
                /*for (int i = 0; i < obstacles.size(); i++) {
                    delete obstacles[i];
                }*/

                return "next scene";
            }
        }
    }

    environment.draw(window, backgroundSprite);

    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i]->draw(window, obstacleSprite);
    }

    player.draw(window, playerSprite);

    scoreboard.draw(window, score);

    return "next frame";
}

/// <summary>
/// Be really really really really careful with memory here.
/// </summary>
//bool Game::play(sf::RenderWindow & window, sf::Sprite & playerSprite, sf::Sprite & backgroundSprite, sf::Sprite & obstacleSprite, Score & score, Time & time, Scoreboard & scoreboard) const {
//
//    while (window.isOpen())
//    {
//        // we do this hereb ecause we dont want a dead window for the draw .. ??
//        sf::Event event;
//        
//        if (checkExitCondition(event, window)) {
//            for (int i = 0; i < obstacles.size(); i++) {
//                delete obstacles[i];
//            }
//
//            return true;
//        }
//
//        for (int i = 0; i < time.processFrame(); i++) {
//            environment.move(time);
//            player.move(time);
//
//            for (int j = 0; j < obstacles.size(); j++) {
//                obstacles[j]->move(time);
//
//                if (player.checkCollision(score, *obstacles[j])) {
//                    for (int i = 0; i < obstacles.size(); i++) {
//                        delete obstacles[i];
//                    }
//                    
//                    // here we wanna go to next scene bascially.
//                    return false;
//
//                    // https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index
//                    // vec.erase(vec.begin() + index);
//
//                    // no not this.
//                    //obstacles.erase(obstacles.begin() + j);
//
//                    //obstacles[j]->resetPosition();
//                }
//            }
//        }
//
//        // so that we see where holes and transparency.
//        window.clear(sf::Color::Magenta);
//
//        environment.draw(window, backgroundSprite);
//
//        for (int i = 0; i < obstacles.size(); i++) {
//            obstacles[i]->draw(window, obstacleSprite);
//        }
//
//        player.draw(window, playerSprite);
//
//        scoreboard.draw(window, score);
//
//        window.display();
//    }
//
//    for (int i = 0; i < obstacles.size(); i++)
//    {
//        delete obstacles[i];
//    }
//
//    print("Closing game.");
//
//    return false;
//}